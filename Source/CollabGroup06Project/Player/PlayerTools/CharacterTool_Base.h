#pragma once

#include "CoreMinimal.h"
#include "CollabGroup06Project/Interfaces/HeldItemInteractable.h"
#include "GameFramework/Actor.h"
#include "CharacterTool_Base.generated.h"

class APlayerCharacter;

UCLASS()
class COLLABGROUP06PROJECT_API ACharacterTool_Base : public AActor, public IHeldItemInteractable
{
	GENERATED_BODY()

public:
	ACharacterTool_Base();
	
	virtual void TakePhoto_Implementation(APlayerCharacter* player,  UUserWidget* journal) override;

	virtual void ToggleCamera_Implementation(APlayerCharacter* player) override;
	
protected:
	virtual void BeginPlay() override;
};
