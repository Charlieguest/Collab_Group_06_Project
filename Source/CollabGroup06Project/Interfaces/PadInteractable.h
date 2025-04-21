
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PadInteractable.generated.h"

UINTERFACE(MinimalAPI)
class UPadInteractable : public UInterface
{
	GENERATED_BODY()
};

class COLLABGROUP06PROJECT_API IPadInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PadActive();

};
