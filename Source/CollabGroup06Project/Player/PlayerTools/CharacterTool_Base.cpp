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

bool ACharacterTool_Base::Fire_Implementation(FVector forward)
{
	return IFireable::Fire_Implementation(forward);
}

void ACharacterTool_Base::Fire_Stop_Implementation()
{
	IFireable::Fire_Stop_Implementation();
}

void ACharacterTool_Base::Grapple_Aim_Implementation(APlayerCharacter* player)
{
	IFireable::Grapple_Aim_Implementation(player);
}

void ACharacterTool_Base::Grapple_Aim_Released_Implementation(APlayerCharacter* player)
{
	IFireable::Grapple_Aim_Released_Implementation(player);
}

void ACharacterTool_Base::Scan_Implementation(APlayerCharacter* player)
{
	IHeldItemInteractable::Scan_Implementation(player);
}

void ACharacterTool_Base::RemoveBerry_Implementation()
{
	IBerryRemovable::RemoveBerry_Implementation();
}

void ACharacterTool_Base::AttachBerry()
{
}

void ACharacterTool_Base::BeginPlay()
{
	Super::BeginPlay();
	
}
