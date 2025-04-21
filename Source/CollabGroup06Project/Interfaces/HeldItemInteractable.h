
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HeldItemInteractable.generated.h"

UINTERFACE()
class UHeldItemInteractable : public UInterface
{
	GENERATED_BODY()
};

class COLLABGROUP06PROJECT_API IHeldItemInteractable
{
	GENERATED_BODY()
	
	public:
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TakePhoto(APlayerCharacter* player, UUserWidget* journal);

		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void ToggleCamera(APlayerCharacter* player);

		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Scan(APlayerCharacter* player);
};
