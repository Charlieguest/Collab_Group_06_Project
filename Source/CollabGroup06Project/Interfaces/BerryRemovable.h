#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BerryRemovable.generated.h"

UINTERFACE()
class UBerryRemovable : public UInterface
{
	GENERATED_BODY()
};

class COLLABGROUP06PROJECT_API IBerryRemovable
{
public:
	GENERATED_BODY()

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RemoveBerry();
};
