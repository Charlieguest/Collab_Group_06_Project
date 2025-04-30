#include "BerryPickup.h"

#include "CollabGroup06Project/Player/PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ABerryPickup::ABerryPickup()
{
	_CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));

	RootComponent = _CollisionComponent;
	_CollisionComponent->SetSimulatePhysics(true);
}

void ABerryPickup::PulltoPlayerPos(FVector playerPos)
{
	FVector distance = playerPos - GetActorLocation();
	//distance.Normalize(0.0001f);
	
	_CollisionComponent->AddForce(distance * 500);
}

void ABerryPickup::PickupBerry_Implementation()
{
	IBerryAquireable::PickupBerry_Implementation();
	Destroy();
}

void ABerryPickup::BeginPlay()
{
	Super::BeginPlay();
}
