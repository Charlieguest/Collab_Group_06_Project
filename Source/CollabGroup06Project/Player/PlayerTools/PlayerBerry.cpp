#include "PlayerBerry.h"
#include "Components/SphereComponent.h"

APlayerBerry::APlayerBerry()
{
	_Root = CreateDefaultSubobject<USphereComponent>(TEXT("SceneRoot"));
	RootComponent = _Root;
}

void APlayerBerry::BeginPlay()
{
	Super::BeginPlay();
}