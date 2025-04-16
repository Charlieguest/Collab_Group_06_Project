#include "CharacterTool_Base.h"

ACharacterTool_Base::ACharacterTool_Base()
{
}

void ACharacterTool_Base::TakePhoto_Implementation(APlayerCharacter* player, UUserWidget* journal)
{
	IHeldItemInteractable::TakePhoto_Implementation(player, journal);
}

void ACharacterTool_Base::ToggleCamera_Implementation(APlayerCharacter* player)
{
	IHeldItemInteractable::ToggleCamera_Implementation(player);
}

void ACharacterTool_Base::BeginPlay()
{
	Super::BeginPlay();
	
}
