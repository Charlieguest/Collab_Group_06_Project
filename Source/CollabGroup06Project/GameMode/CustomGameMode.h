#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CustomGameMode.generated.h"

class APlayerCharController;
class UGameRule;

UCLASS()
class COLLABGROUP06PROJECT_API ACustomGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ACustomGameMode();

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	virtual void BeginPlay() override;

	UFUNCTION()
	void DecreaseCountdown();
	
	UFUNCTION()
	void Handle_GameRuleCompleted(UGameRule* rule);

	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;

	virtual void OnMatchStateSet() override;

	virtual bool ReadyToStartMatch_Implementation() override;
	virtual bool ReadyToEndMatch_Implementation() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=MatchManagement)
	int _CountDownTimer = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=MatchManagement)
	int _GameRulesLeft;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<TObjectPtr<UGameRule>, bool> _GameRuleManagers;

	FTimerHandle _TimerDecreaseCountdown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<AController>> _PlayerControllers;
	
	TObjectPtr<APlayerCharController> _PlayerCharController;
	
};
