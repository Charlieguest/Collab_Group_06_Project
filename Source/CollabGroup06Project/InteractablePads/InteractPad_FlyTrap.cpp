﻿#include "InteractPad_FlyTrap.h"


AInteractPad_FlyTrap::AInteractPad_FlyTrap()
{
	isActive = false;
}

void AInteractPad_FlyTrap::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractPad_FlyTrap::PadActive_Implementation()
{
	Super::PadActive_Implementation();
	
	isActive = true;

	PadActivated();
	// Play some animation of the plant moving to an active state
}

void AInteractPad_FlyTrap::PadActivated_Implementation()
{
}
