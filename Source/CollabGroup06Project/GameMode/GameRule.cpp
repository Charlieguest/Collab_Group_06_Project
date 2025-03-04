#include "GameRule.h"

UGameRule::UGameRule()
{
	_IsOptional = false;
}

void UGameRule::BroadcastGameRuleComplete()
{
	OnGameRuleComplete.Broadcast(this);
}

void UGameRule::Init()
{
	
}