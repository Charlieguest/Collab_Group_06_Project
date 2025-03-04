#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MatchStateHandler.generated.h"

UINTERFACE()
class UMatchStateHandler : public UInterface
{
	GENERATED_BODY()
};

class COLLABGROUP06PROJECT_API IMatchStateHandler
{
	GENERATED_BODY()

	public:
		UFUNCTION(BlueprintNativeEvent)
		void Handle_MatchStarted();

		UFUNCTION(BlueprintNativeEvent)
		void Handle_MatchEnded();
};
