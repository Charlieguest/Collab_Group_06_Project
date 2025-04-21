#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Fireable.generated.h"

class APlayerCharacter;

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
	bool Fire(FVector forward);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Fire_Stop();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Grapple_Aim(APlayerCharacter* player);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Grapple_Aim_Released(APlayerCharacter* player);
};
