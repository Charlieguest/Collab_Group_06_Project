#pragma once

#include "CoreMinimal.h"
#include "CollabGroup06Project/Interfaces/BerryRemovable.h"
#include "CollabGroup06Project/Interfaces/Fireable.h"
#include "CollabGroup06Project/Interfaces/HeldItemInteractable.h"
#include "GameFramework/Actor.h"
#include "CharacterTool_Base.generated.h"

class APlayerCharacter;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAnimalPhotoTaken, FString, animalType, ACreature_Base*, animal, UUserWidget*, screenshotInstance);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGrappleStartSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGrappleDuringSignature, FVector, GrabPoint,  float, GrabForce);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGrappleEndSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGrappleBerrySignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRelasePlayerSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCameraAimSignature, bool, isHoldingCamera);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAddCrossHairSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRemoveCrossHairSignature);


UCLASS()
class COLLABGROUP06PROJECT_API ACharacterTool_Base : public AActor, public IHeldItemInteractable, public IFireable, public IBerryRemovable
{
	GENERATED_BODY()

public:
	ACharacterTool_Base();
	
	virtual void TakePhoto_Implementation(APlayerCharacter* player,  UUserWidget* journal) override;

	virtual void ToggleCamera_Implementation(APlayerCharacter* player) override;

	virtual bool Fire_Implementation(FVector forward) override;
	
	virtual void Fire_Stop_Implementation() override;

	virtual void Grapple_Aim_Implementation(APlayerCharacter* player) override;

	virtual void Grapple_Aim_Released_Implementation(APlayerCharacter* player) override;

	virtual void Scan_Implementation(APlayerCharacter* player) override;

	virtual void RemoveBerry_Implementation() override;

	virtual void AttachBerry();
	
	FAnimalPhotoTaken OnSuccessfulAnimalPhotoTaken;

	FGrappleStartSignature OnGrappleStart;
	FGrappleDuringSignature OnGrappleDuring;
	FGrappleEndSignature OnGrappleEnd;
	FGrappleBerrySignature OnGrappleBerry;

	FRelasePlayerSignature OnReleasePlayer;
	
	FCameraAimSignature OnHoldingCamera;

	FAddCrossHairSignature OnAddCrossHair;

	FRemoveCrossHairSignature OnRemoveCrossHair;
	
protected:
	virtual void BeginPlay() override;
};
