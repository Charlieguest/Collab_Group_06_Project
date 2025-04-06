#include "PlayerBerry.h"
#include "Components/SphereComponent.h"

APlayerBerry::APlayerBerry()
{
	_Root = CreateDefaultSubobject<USphereComponent>(TEXT("SceneRoot"));
	RootComponent = _Root;

	_AttachedBerryMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BerryMesh"));
	_AttachedBerryMesh->SetupAttachment(RootComponent);
}

void APlayerBerry::BeginPlay()
{
	Super::BeginPlay();
}