
#include "InteractPad_Base.h"

#include "Components/SphereComponent.h"

AInteractPad_Base::AInteractPad_Base()
{
	_AssetRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Asset Root"));
	_AssetRoot->SetupAttachment(RootComponent);

	_AssetCollisionPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Asset Collision Pivot"));
	_AssetCollisionPivot->SetupAttachment(_AssetRoot);
	
	_CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Player Collider"));
	_CollisionComp->SetupAttachment(_AssetCollisionPivot);

	_ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	_ArrowComp->SetupAttachment(_AssetRoot);

	_GrappleCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("Grapple Collision"));
	_GrappleCollisionComp->SetupAttachment(_AssetRoot);
	_GrappleCollisionComp->InitSphereRadius(6.0f);
	_GrappleCollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
}

void AInteractPad_Base::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractPad_Base::PadActive_Implementation()
{
	IPadInteractable::PadActive_Implementation();
	switch (isActive)
	{
	case true:
		isActive = false;
		break;
	case false:
		isActive = true;
		break;
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Red, FString::Printf(TEXT("Works %s"), isActive ? TEXT("TRUE") : TEXT("FALSE")));
}

void AInteractPad_Base::CompletePlantAction_Implementation()
{
	//Complete Blueprint Functionality
}

void AInteractPad_Base::PlantActionEnd_Implementation()
{
	//End Plant Blueprint Functionality
}

void AInteractPad_Base::OnOverlapBeginBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AInteractPad_Base::OnOverlapEndBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


