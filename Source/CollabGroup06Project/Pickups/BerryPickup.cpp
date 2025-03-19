#include "BerryPickup.h"
#include "Components/SphereComponent.h"

ABerryPickup::ABerryPickup()
{
	_CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	RootComponent = _CollisionComponent;
	_CollisionComponent->SetSimulatePhysics(true);
}

void ABerryPickup::interact_Implementation()
{
	IInteract::interact_Implementation();
	Destroy();
}

void ABerryPickup::PulltoPlayerPos(FVector playerPos)
{
	FVector distance = playerPos - GetActorLocation();
	//distance.Normalize(0.0001f);
	
	_CollisionComponent->AddForce(distance * 500);
}

void ABerryPickup::BeginPlay()
{
	Super::BeginPlay();
}