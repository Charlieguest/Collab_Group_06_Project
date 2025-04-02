#include "GrappleGun.h"
#include "CableComponent.h"
#include "PlayerBerry.h"
#include "CollabGroup06Project/InteractablePads/InteractPad_FlyTrap.h"
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

	if(_AttachedBerry != nullptr)
	{
		_AttachedBerry->_AttachedBerryMesh->SetVisibility(false);
	}
	
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	SpawnParameters.Instigator = GetInstigator();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	//Spawning actor
	AActor* grapple = world->SpawnActor(_ProjectileRef, &_BerryAttachPoint->GetComponentTransform(), SpawnParameters);
	_GrappleProjectile = Cast<AGrappleProjectile>(grapple);

	//Listening to hit events
	_GrappleProjectile->CollisionComp->OnComponentHit.AddDynamic(this, &AGrappleGun::OnProjectileHit);
	_GrappleProjectile->OnRemoveBerry.AddUniqueDynamic(this, &AGrappleGun::RemoveBerry);
	
	if(_HasBerry)
	{
		_GrappleProjectile->AttachBerryProjectile();
	}

	GetWorld()->GetTimerManager().SetTimer(_InitialProjectileTimerHandle, this, &AGrappleGun::InitialProjectileTimer, 0.1f, false);
	
	//Applying Force
	_GrappleProjectile->CollisionComp->AddImpulse(Forward * _ProjectileSpeed);

	_HasFired = true;
	return true;
}

void AGrappleGun::Fire_Stop_Implementation()
{
	IFireable::Fire_Stop_Implementation();
	
	_IsGrapplingPlayer = false;
	_IsGrapplingBerry = false;
	_HasFired = false;
	
	OnGrappleEnd.Broadcast();

	_Cable->SetVisibility(false);
	
	if(_BerryGrappleTimerDelegate.IsBound())
	{
		_BerryGrappleTimerDelegate.Unbind();
	}
	
	DestroyGrappleProjectile();

	if(_AttachedBerry != nullptr)
	{
		_AttachedBerry->_AttachedBerryMesh->SetVisibility(true);
	}
}

void AGrappleGun::OnProjectileHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{

	ABerryPickup* BerryPickup = Cast<ABerryPickup>(OtherActor);
	AInteractPad_FlyTrap* Flytrap = Cast<AInteractPad_FlyTrap>(OtherActor);
	
	if(BerryPickup != nullptr)
	{
		DestroyGrappleProjectile();
		_IsGrapplingBerry = true;
		_Cable->EndLocation = GetActorTransform().InverseTransformPosition(OtherActor->GetActorLocation());
		_Cable->SetVisibility(true);
		_BerryGrappleTimerDelegate.BindUFunction(this, FName("GrappleBerry"), BerryPickup);
		GetWorld()->GetTimerManager().SetTimer(_BerryGrappleTimer, _BerryGrappleTimerDelegate, 0.05f, false);
	}
	else if(Flytrap != nullptr && Flytrap->isActive)
	{
		_IsGrapplingPlayer = true;
		
		OnGrappleStart.Broadcast();
		_ProjectileHitLoc = Hit.ImpactPoint;
		_Cable->EndLocation = GetActorTransform().InverseTransformPosition(_ProjectileHitLoc);
		_Cable->SetVisibility(true);
		GetWorld()->GetTimerManager().SetTimer(_PlayerGrappleTimer, this, &AGrappleGun::GrapplePlayer, 0.05f, false);
	}
	else
	{
		//Hit nothing relevant to grapple to
		DestroyGrappleProjectile();
	}
}

void AGrappleGun::GrapplePlayer()
{
	if(!_IsGrapplingPlayer)
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
	if(!_IsGrapplingBerry)
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

void AGrappleGun::AttachBerry()
{
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	
	AActor* playerBerry = GetWorld()->SpawnActor(_AttachedBerryRef, &_BerryAttachPoint->GetComponentTransform(), spawnParams);
	playerBerry->AttachToComponent(_BerryAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);

	_AttachedBerry = Cast<APlayerBerry>(playerBerry);
	
	_HasBerry = true;
}

void AGrappleGun::DestroyGrappleProjectile()
{
	if(_GrappleProjectile != nullptr)
	{
		//Destroying Berry on Projectile

		TArray<AActor*> attachedProjectileActors;
		
		_GrappleProjectile->GetAttachedActors(attachedProjectileActors, false, false);

		if(attachedProjectileActors.Num() > 0)
		{
			for(AActor* berry : attachedProjectileActors)
			{
				berry->Destroy();
			}
		}
		_HasFired = false;
		_GrappleProjectile->Destroy();
	}
}

void AGrappleGun::RemoveBerry()
{
	_HasBerry = false;
	if(_AttachedBerry != nullptr)
	{
		_AttachedBerry->Destroy();
	}
}

void AGrappleGun::InitialProjectileTimer()
{

	if(!_HasFired)
	{
	}
	else if(!_IsGrapplingBerry && !_IsGrapplingPlayer)
	{
		FVector currentProjectileDist = this->GetActorLocation() - _GrappleProjectile->GetActorLocation();
		
		if(abs(currentProjectileDist.X) > _MaxFireDistance ||
		   abs(currentProjectileDist.Y) > _MaxFireDistance ||
		   abs(currentProjectileDist.Z) > _MaxFireDistance 
		   )
		{
				DestroyGrappleProjectile();
		}
		
		GetWorld()->GetTimerManager().SetTimer(_PlayerGrappleTimer, this, &AGrappleGun::InitialProjectileTimer, 0.01f, false);
	}
}
