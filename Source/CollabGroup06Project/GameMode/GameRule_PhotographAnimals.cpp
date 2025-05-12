#include "GameRule_PhotographAnimals.h"

#include "CollabGroup06Project/Creatures/Creature_Base.h"
#include "Kismet/GameplayStatics.h"


UGameRule_PhotographAnimals::UGameRule_PhotographAnimals()
{
	_CreaturesRemaining = 0;
}

void UGameRule_PhotographAnimals::Init()
{
	if(_Creatures.Num() == 0)
	{
		TArray<AActor*> outActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACreature_Base::StaticClass(), outActors);
		for(AActor* a : outActors)
		{
			_Creatures.Add(Cast<ACreature_Base>(a));
		}
	}

	_CreaturesRemaining = _Creatures.Num();
	
	for(ACreature_Base* creature : _Creatures)
	{
		//Bind to relevant events
		creature->OnAnimalPhotographed.AddUniqueDynamic(this, &UGameRule_PhotographAnimals::Handle_Photographed);
	}
}

void UGameRule_PhotographAnimals::BeginPlay()
{
	Super::BeginPlay();
}

void UGameRule_PhotographAnimals::Handle_Photographed()
{
	_CreaturesRemaining--;

	if(_CreaturesRemaining == 0)
	{
		BroadcastGameRuleComplete();
	}
}
