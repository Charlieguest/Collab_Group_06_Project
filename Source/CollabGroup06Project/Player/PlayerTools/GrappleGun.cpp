#include "GrappleGun.h"
#include "CableComponent.h"
#include "CollabGroup06Project/Pickups/BerryPickup.h"
#include "CollabGroup06Project/Projectiles/GrappleProjectile.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponProj, Display, All);

AGrappleGun::AGrappleGun()
{
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;

	_BerryAttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("BerryAttachPoint"));
	_BerryAttachPoint->SetupAttachment(_Root);
	
	_Cable = CreateDefaultSubobject<UCableComponent>(TEXT("GrappleCable"));
	_Cable->SetupAttachment(_Root);
}

void AGrappleGun::BeginPlay()
{
	Super::BeginPlay();

	_Cable->SetVisibility(false);
}

bool AGrappleGun::Fire_Implementation(FVector Forward)
{
	UWorld* const world = GetWorld();

	if (world == nullptr || _ProjectileRef == nullptr || _HasFired == true) {  return false; }
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	SpawnParameters.Instigator = GetInstigator();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

	AActor* grapple = world->SpawnActor(_ProjectileRef, &_BerryAttachPoint->GetComponentTransform(), SpawnParameters);
	_GrappleProjectile = Cast<AGrappleProjectile>(grapple);

	_GrappleProjectile->CollisionComp->OnComponentHit.AddDynamic(this, &AGrappleGun::OnProjectileHit);
	_GrappleProjectile->CollisionComp->AddImpulse(Forward * _ProjectileSpeed);
	
	_FireTime = 1;
	_HasFired = true;
	
	return true;
}

void AGrappleGun::Fire_Stop_Implementation()
{
	IFireable::Fire_Stop_Implementation();
	
	_IsGrappling = false;
	_HasFired = false;
	
	OnGrappleEnd.Broadcast();

	_Cable->SetVisibility(false);
	
	if(_BerryGrappleTimerDelegate.IsBound())
	{
		_BerryGrappleTimerDelegate.Unbind();
	}
	
	if(_GrappleProjectile != nullptr)
	{
		_GrappleProjectile->Destroy();
	}
}

void AGrappleGun::OnProjectileHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{

	ABerryPickup* BerryPickup = Cast<ABerryPickup>(OtherActor);
	
	if(BerryPickup != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, OtherActor->GetName());

		_IsGrappling = true;
		_Cable->EndLocation = GetActorTransform().InverseTransformPosition(OtherActor->GetActorLocation());
		_Cable->SetVisibility(true);
		_BerryGrappleTimerDelegate.BindUFunction(this, FName("GrappleBerry"), BerryPickup);
		GetWorld()->GetTimerManager().SetTimer(_BerryGrappleTimer, _BerryGrappleTimerDelegate, 0.05f, false);
	}
	else
	{
		_IsGrappling = true;
		
		OnGrappleStart.Broadcast();
		_ProjectileHitLoc = Hit.ImpactPoint;
		_Cable->EndLocation = GetActorTransform().InverseTransformPosition(_ProjectileHitLoc);
		_Cable->SetVisibility(true);
		GetWorld()->GetTimerManager().SetTimer(_PlayerGrappleTimer, this, &AGrappleGun::GrapplePlayer, 0.05f, false);
	}
}

void AGrappleGun::GrapplePlayer()
{
	if(!_IsGrappling)
	{
		//Stop the timer
	}
	else
	{
		OnGrappleDuring.Broadcast(_ProjectileHitLoc);
		_Cable->EndLocation = GetActorTransform().InverseTransformPosition(_ProjectileHitLoc);
		GetWorld()->GetTimerManager().SetTimer(_PlayerGrappleTimer, this, &AGrappleGun::GrapplePlayer, 0.01f, false);
	}
}

void AGrappleGun::GrappleBerry(ABerryPickup* BerryPickup)
{
	if(!_IsGrappling)
	{
		//Stop the timer
	}
	else
	{
		_Cable->EndLocation = GetActorTransform().InverseTransformPosition(BerryPickup->GetActorLocation());
		BerryPickup->PulltoPlayerPos(GetOwner()->GetActorLocation());
		GetWorld()->GetTimerManager().SetTimer(_BerryGrappleTimer, _BerryGrappleTimerDelegate, 0.01f, false);
	}
}
