#pragma once

#include "CoreMinimal.h"
#include "CharacterTool_Base.h"
#include "CharacterTool_Scan.generated.h"

UCLASS()
class COLLABGROUP06PROJECT_API ACharacterTool_Scan : public ACharacterTool_Base
{
	GENERATED_BODY()

public:
	ACharacterTool_Scan();

protected:
	virtual void BeginPlay() override;
};
