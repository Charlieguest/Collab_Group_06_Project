#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BerryAquireable.generated.h"

UINTERFACE()
class UBerryAquireable : public UInterface
{
	GENERATED_BODY()
};

class COLLABGROUP06PROJECT_API IBerryAquireable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PickupBerry();
};
