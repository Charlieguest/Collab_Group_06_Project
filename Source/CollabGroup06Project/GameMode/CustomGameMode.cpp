#include "CustomGameMode.h"

#include "GameRule.h"

ACustomGameMode::ACustomGameMode()
{
	
}

void ACustomGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}

void ACustomGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Collecting all the GameMode's GameRule Components
	TArray<UActorComponent*> outComponents;
	GetComponents(outComponents);

	for(UActorComponent* comp : outComponents)
	{
		if(UGameRule* rule = Cast<UGameRule>(comp))
		{
			_GameRuleManagers.Add(rule, rule->_IsOptional);
			rule->Init();
			rule->OnGameRuleComplete.AddDynamic(this, &ACustomGameMode::Handle_GameRuleCompleted);
			if(!rule->_IsOptional)
			{
				_GameRulesLeft++;
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, FString::Printf(TEXT("Rule Count: %d"), _GameRulesLeft));
			}
		}
	}
}

void ACustomGameMode::DecreaseCountdown()
{
	_CountDownTimer--;

	if (_CountDownTimer == 0)
	{
		StartMatch();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(_TimerDecreaseCountdown, this, &ACustomGameMode::DecreaseCountdown, 1.f, false);
	}
}

void ACustomGameMode::HandleMatchIsWaitingToStart()
{
	Super::HandleMatchIsWaitingToStart();
	GetWorld()->GetTimerManager().SetTimer(_TimerDecreaseCountdown, this, &ACustomGameMode::DecreaseCountdown, 1.f, false);
}

void ACustomGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	//TODO: INITIALISE PLAYER CONTROLLER
}

void ACustomGameMode::HandleMatchHasEnded()
{
	Super::HandleMatchHasEnded();

	//TODO: INITIALISE PLAYER CONTROLLER
}

void ACustomGameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();
	
	FString output;
	
	if(MatchState == MatchState::WaitingToStart)
	{
		output = "waiting to start";
	}
	else if(MatchState == MatchState::InProgress)
	{
		output = "In Progress";
	}
	else if(MatchState == MatchState::WaitingPostMatch)
	{
		output = "Waiting for post match";
	}
	else if(MatchState == MatchState::LeavingMap)
	{
		output = "Leaving Map";
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("State Changed to: %s"), *output));
}

void ACustomGameMode::Handle_GameRuleCompleted(UGameRule* rule)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString::Printf(TEXT("Game Completed")));
	if(!_GameRuleManagers.Find(rule)) { return; }

	_GameRulesLeft--;
	
	if(_GameRulesLeft != 0) { return; }

	EndMatch();
}

void ACustomGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

//Below are checker functions
//These return whether we're a ready to move on with the match stages
//The result of which can be called and checked against in other functions.
bool ACustomGameMode::ReadyToStartMatch_Implementation()
{
	return false;
}

bool ACustomGameMode::ReadyToEndMatch_Implementation()
{
	return false;
}