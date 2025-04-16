#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PhotoTakeable.generated.h"

class APlayerCharacter;

UINTERFACE()
class UPhotoTakeable : public UInterface
{
	GENERATED_BODY()
};

class COLLABGROUP06PROJECT_API IPhotoTakeable
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TakePhoto(APlayerCharacter* player, UUserWidget* journal);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ToggleCamera(APlayerCharacter* player);
};
