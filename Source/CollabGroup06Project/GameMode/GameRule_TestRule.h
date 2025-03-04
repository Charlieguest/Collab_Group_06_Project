#pragma once

#include "CoreMinimal.h"
#include "GameRule.h"
#include "GameRule_TestRule.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COLLABGROUP06PROJECT_API UGameRule_TestRule : public UGameRule
{
	GENERATED_BODY()

public:
	UGameRule_TestRule();
	

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void DecreaseCountdown();

	int _CountDownTimer = 2;
	FTimerHandle _TimerDecreaseCountdown;
};
