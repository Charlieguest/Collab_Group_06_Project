#include "GrappleGun.h"

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
	AGrappleProjectile* GrappleProjectile = Cast<AGrappleProjectile>(grapple);

	GrappleProjectile->CollisionComp->AddImpulse(Forward * _ProjectileSpeed);
	
	_FireTime = 1;
	_HasFired = true;
	GetWorld()->GetTimerManager().SetTimer(_FireStopTimer, this, &AGrappleGun::FireStopCountdown, 1.0f, false);
	
	return true;
}

void AGrappleGun::BeginPlay()
{
	Super::BeginPlay();
}

void AGrappleGun::FireStopCountdown()
{
	_FireTime--;
	
	if(_FireTime == 0)
	{
		_HasFired = false;	
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(_FireStopTimer, this, &AGrappleGun::FireStopCountdown, 1.0f, false);
	}
}
