// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InputActionable.generated.h"

UINTERFACE()
class UInputActionable : public UInterface
{
	GENERATED_BODY()
};


class COLLABGROUP06PROJECT_API IInputActionable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Jump(const FInputActionValue& Instance);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Move(const FInputActionValue& Instance);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Look(const FInputActionValue& Instance);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ToggleInventory(const FInputActionValue& Intance);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ToggleJournal(const FInputActionValue& Instance);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Combine(const FInputActionValue& Instance);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PrimaryInteract(const FInputActionValue& Instance);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CompletedPrimaryInteract(const FInputActionValue& Instance);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact(const FInputActionValue& Instance);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Aim(const FInputActionValue& Instance);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AimReleased(const FInputActionValue& Instance);
};
