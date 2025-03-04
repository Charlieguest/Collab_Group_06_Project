#include "GameRule_TestRule.h"


UGameRule_TestRule::UGameRule_TestRule()
{
	
}

// Called when the game starts
void UGameRule_TestRule::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(_TimerDecreaseCountdown, this, &UGameRule_TestRule::DecreaseCountdown, 1.f, false);

}

void UGameRule_TestRule::DecreaseCountdown()
{
	_CountDownTimer--;
	
	if (_CountDownTimer == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, FString::Printf(TEXT("Test Game Rule Complete")));
		BroadcastGameRuleComplete();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(_TimerDecreaseCountdown, this, &UGameRule_TestRule::DecreaseCountdown, 1.f, false);
	}
}
