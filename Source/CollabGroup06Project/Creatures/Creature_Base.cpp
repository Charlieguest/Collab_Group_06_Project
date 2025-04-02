#include "Creature_Base.h"

ACreature_Base::ACreature_Base()
{

}

void ACreature_Base::interact_Implementation()
{
	IInteract::interact_Implementation();
}

void ACreature_Base::BeginPlay()
{
	Super::BeginPlay();
}
