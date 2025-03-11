#include "GrappleProjectile.h"

#include "Components/SphereComponent.h"

AGrappleProjectile::AGrappleProjectile()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(3.0f);
	CollisionComp->OnComponentHit.AddDynamic(this, &AGrappleProjectile::OnHit);

	//Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set Collision as Root
	RootComponent = CollisionComp;

	InitialLifeSpan = 3;
}

void AGrappleProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AGrappleProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Green, FString::Printf(TEXT("Test Collision")));
}
