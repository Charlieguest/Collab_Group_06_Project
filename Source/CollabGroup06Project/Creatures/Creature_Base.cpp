#include "Creature_Base.h"

ACreature_Base::ACreature_Base()
{
	_IsPhotographable = false;
}

void ACreature_Base::interact_Implementation()
{
	IInteract::interact_Implementation();
}

void ACreature_Base::BeginPlay()
{
	Super::BeginPlay();
}
