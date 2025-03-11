#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Fireable.generated.h"

UINTERFACE()
class UFireable : public UInterface
{
	GENERATED_BODY()
};

class COLLABGROUP06PROJECT_API IFireable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool Fire();
};
