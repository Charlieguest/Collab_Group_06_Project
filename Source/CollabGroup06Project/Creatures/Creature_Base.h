#pragma once

#include "CoreMinimal.h"
#include "CollabGroup06Project/Interfaces/Interact.h"
#include "GameFramework/Character.h"
#include "Creature_Base.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnimalPhotographedSignature);

UCLASS()
class COLLABGROUP06PROJECT_API ACreature_Base : public ACharacter, public IInteract
{
	GENERATED_BODY()
public:
	ACreature_Base();

	virtual void interact_Implementation() override;

	// This is C++ as we need access to check against the player's inventory
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString _RequiredItemName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool _IsPhotographable;

	FAnimalPhotographedSignature OnAnimalPhotographed;

protected:
	virtual void BeginPlay() override;

};
