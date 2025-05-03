// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractUI.generated.h"

UINTERFACE()
class UInteractUI : public UInterface
{
	GENERATED_BODY()
};

class COLLABGROUP06PROJECT_API IInteractUI
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InteractUI(const FString& InteractMessage);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InteractUIOff();
};
