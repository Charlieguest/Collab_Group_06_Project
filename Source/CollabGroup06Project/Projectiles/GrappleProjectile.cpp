#include "GrappleProjectile.h"

#include "CollabGroup06Project/Pickups/BerryPickup.h"
#include "Components/SphereComponent.h"

AGrappleProjectile::AGrappleProjectile()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(6.0f);
	CollisionComp->SetSimulatePhysics(true);
	CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	CollisionComp->OnComponentHit.AddDynamic(this, &AGrappleProjectile::OnHit);

	//Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set Collision as Root
	RootComponent = CollisionComp;

	InitialLifeSpan = 0;
}

void AGrappleProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AGrappleProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{

	ABerryPickup* BerryPickup = Cast<ABerryPickup>(OtherActor);

	if(BerryPickup != nullptr)
	{
		Destroy();
	}
	else
	{
		CollisionComp->SetSimulatePhysics(false);
		CollisionComp->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	}
	

}


