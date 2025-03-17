#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BerryPickup.generated.h"

class USphereComponent;

UCLASS()
class COLLABGROUP06PROJECT_API ABerryPickup : public AActor
{
	GENERATED_BODY()

public:
	ABerryPickup();

	void PulltoPlayerPos(FVector playerPos);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> _CollisionComponent;
	
protected:
	virtual void BeginPlay() override;
	
};