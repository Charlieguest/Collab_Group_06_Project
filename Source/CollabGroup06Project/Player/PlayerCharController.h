#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "CollabGroup06Project/Interfaces/MatchStateHandler.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharController.generated.h"

class UInputAssets;
class UInputMappingContext;

struct FInputAssetInstance;
struct FInputActionValue;

UCLASS()
class COLLABGROUP06PROJECT_API APlayerCharController : public APlayerController, public IMatchStateHandler
{
	GENERATED_BODY()

public:
	APlayerCharController();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintNativeEvent)
	void Init();

	virtual void Handle_MatchStarted_Implementation() override;
	virtual void Handle_MatchEnded_Implementation() override;

	//----------------------
	// Input Handler Functions
	//----------------------

	UFUNCTION()
	void CAM_Jump(const FInputActionValue& Instance);

	void CAM_Move(const FInputActionValue& Instance);

	void CAM_Look(const FInputActionValue& Instance);

	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> _PawnToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APawn> _PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=InputMapping, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* _InputMappingContext;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UInputAssets> _InputActions;

};
