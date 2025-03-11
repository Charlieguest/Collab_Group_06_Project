#include "GrappleGun.h"

#include "CollabGroup06Project/Projectiles/GrappleProjectile.h"
#include "Components/ArrowComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponProj, Display, All);

AGrappleGun::AGrappleGun()
{
	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;

	_BerryAttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("BerryAttachPoint"));
	_BerryAttachPoint->SetupAttachment(_Root);
}

bool AGrappleGun::Fire_Implementation()
{
	UWorld* const world = GetWorld();
	GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Green, FString::Printf(TEXT("Function Fires")));

	if (world == nullptr || _ProjectileRef == nullptr) {  return false; }

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	SpawnParameters.Instigator = GetInstigator();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

	world->SpawnActor(_ProjectileRef, &_BerryAttachPoint->GetComponentTransform(), SpawnParameters);
	
	GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Green, FString::Printf(TEXT("Thing Spawns")));
	
	return true;
}

void AGrappleGun::BeginPlay()
{
	Super::BeginPlay();
}
