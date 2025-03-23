#pragma once

#include "CoreMinimal.h"
#include "InteractPad_Base.h"
#include "InteractPad_FlyTrap.generated.h"

UCLASS()
class COLLABGROUP06PROJECT_API AInteractPad_FlyTrap : public AInteractPad_Base
{
	GENERATED_BODY()

public:
	AInteractPad_FlyTrap();

protected:
	virtual void BeginPlay() override;

	virtual void PadActive_Implementation() override;
};
