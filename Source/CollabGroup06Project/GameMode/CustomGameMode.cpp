﻿#include "CustomGameMode.h"

#include "GameRule.h"
#include "CollabGroup06Project/Interfaces/MatchStateHandler.h"
#include "CollabGroup06Project/Player/PlayerCharController.h"
#include "Kismet/KismetSystemLibrary.h"

ACustomGameMode::ACustomGameMode()
{
	
}

void ACustomGameMode::Logout(AController* Exiting)
{
	_PlayerControllers.Remove(Exiting);
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

	//Removing Countdown in this project instance
	//GetWorld()->GetTimerManager().SetTimer(_TimerDecreaseCountdown, this, &ACustomGameMode::DecreaseCountdown, 1.f, false);

	StartMatch();
}

void ACustomGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	for(AController* controller : _PlayerControllers)
	{
		if(UKismetSystemLibrary::DoesImplementInterface(controller, UMatchStateHandler::StaticClass()))
		{
			IMatchStateHandler::Execute_Handle_MatchStarted(controller);
		}
	}
}

void ACustomGameMode::HandleMatchHasEnded()
{
	Super::HandleMatchHasEnded();

	for(AController* controller : _PlayerControllers)
	{
		if(UKismetSystemLibrary::DoesImplementInterface(controller, UMatchStateHandler::StaticClass()))
		{
			IMatchStateHandler::Execute_Handle_MatchEnded(controller);
		}
	}
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
}

void ACustomGameMode::Handle_GameRuleCompleted(UGameRule* rule)
{
	if(!_GameRuleManagers.Find(rule)) { return; }

	_GameRulesLeft--;
	
	if(_GameRulesLeft != 0) { return; }
	
	EndMatch();
	SendToLevelComplete();
}

void ACustomGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	_PlayerControllers.AddUnique(NewPlayer);
	if(APlayerCharController* castedPC = Cast<APlayerCharController>(NewPlayer))
	{
		//TODO: Bind to any relevant events
		castedPC->Init();
		_PlayerCharController = castedPC;
	}
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

void ACustomGameMode::SendToLevelComplete_Implementation()
{
}
