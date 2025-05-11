#include "GrappleProjectile.h"

#include "../InteractablePads/InteractPad_Base.h"
#include "Chaos/ChaosPerfTest.h"
#include "CollabGroup06Project/Pickups/BerryPickup.h"
#include "CollabGroup06Project/Player/PlayerTools/PlayerBerry.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"

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

	_BerryAttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Berry Attach Point"));
	_BerryAttachPoint->SetupAttachment(RootComponent);
}

void AGrappleProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AGrappleProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
/*
	*ABerryPickup* BerryPickup = Cast<ABerryPickup>(OtherActor);
	
		if(BerryPickup != nullptr)
		{
			Destroy();
		}
 */
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "This");
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("%s"), *OtherActor->GetName()));

	if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, UPadInteractable::StaticClass()) & _ProjectileHasBerry & !OtherActor->ActorHasTag(TEXT("NoBerry")))
	{
		OnRemoveBerry.Broadcast();
		
		IPadInteractable::Execute_PadActive(OtherActor);
	}
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UPadInteractable::StaticClass()) & OtherActor->ActorHasTag(TEXT("NoBerry")))
	{
		IPadInteractable::Execute_PadActive(OtherActor);
	}
	
	CollisionComp->SetSimulatePhysics(false);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);


}

void AGrappleProjectile::AttachBerryProjectile()
{
	_ProjectileHasBerry = true;

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;

	AActor* playerBerry = GetWorld()->SpawnActor(_AttachedBerryRef, &_BerryAttachPoint->GetComponentTransform(), spawnParams);
	playerBerry->AttachToComponent(_BerryAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
}
