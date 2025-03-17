// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interact.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInteract : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COLLABGROUP06PROJECT_API IInteract
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	 void interact();
};
