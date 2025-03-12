
#pragma once

#include "CoreMinimal.h"
#include "InteractiveToolObjects.h"
#include "CollabGroup06Project/Interfaces/Fireable.h"
#include "GrappleGun.generated.h"

class AGrappleProjectile;
class UArrowComponent;

UCLASS()
class COLLABGROUP06PROJECT_API AGrappleGun : public AActor, public IFireable
{
	GENERATED_BODY()

public:
	AGrappleGun();
	
	virtual bool Fire_Implementation(FVector Forward) override;

	virtual void BeginPlay() override;

	void FireStopCountdown();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AGrappleProjectile> _ProjectileRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _Root;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> _BerryAttachPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool _HasFired;

	FTimerHandle _FireStopTimer;
	int _FireTime = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _ProjectileSpeed = 10000.0f;
};
