#include "BerryPickup.h"
#include "Components/SphereComponent.h"

ABerryPickup::ABerryPickup()
{
	_CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	RootComponent = _CollisionComponent;
	_CollisionComponent->SetSimulatePhysics(true);
}

void ABerryPickup::PulltoPlayerPos(FVector playerPos)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Green, FString::Printf(TEXT("X: %f, Y: %f, Z: %f"), playerPos.X - GetActorLocation().X, playerPos.Y - GetActorLocation().Y, playerPos.Z - GetActorLocation().Z ));
	FVector distance = playerPos - GetActorLocation();
	//distance.Normalize(0.0001f);
	
	_CollisionComponent->AddForce(distance * 500);
}

void ABerryPickup::BeginPlay()
{
	Super::BeginPlay();
}