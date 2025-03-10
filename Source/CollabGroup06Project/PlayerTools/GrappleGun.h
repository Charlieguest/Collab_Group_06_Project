
#pragma once

#include "CoreMinimal.h"
#include "InteractiveToolObjects.h"
#include "GrappleGun.generated.h"

class UArrowComponent;

UCLASS()
class COLLABGROUP06PROJECT_API AGrappleGun : public AActor
{
	GENERATED_BODY()

public:
	AGrappleGun();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _Root;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> _Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> _BerryAttachPoint;
};
