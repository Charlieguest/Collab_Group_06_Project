#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interact.generated.h"

UINTERFACE()
class UInteract : public UInterface
{
	GENERATED_BODY()
};


class COLLABGROUP06PROJECT_API IInteract
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	 void interact();
};
