#pragma once

#include "CoreMinimal.h"
#include "CollabGroup06Project/Interfaces/BerryAquireable.h"
#include "CollabGroup06Project/Interfaces/Interact.h"
#include "GameFramework/Actor.h"
#include "BerryPickup.generated.h"

class USphereComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBerryPickedup);

UCLASS()
class COLLABGROUP06PROJECT_API ABerryPickup : public AActor, public IBerryAquireable
{
	GENERATED_BODY()

public:
	ABerryPickup();
	
	void PulltoPlayerPos(FVector playerPos);

	virtual void PickupBerry_Implementation() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> _CollisionComponent;

	UFUNCTION(BlueprintNativeEvent)
	void SpawnBerryReplacement();
	
	FOnBerryPickedup _OnPickedUp;
	
protected:
	virtual void BeginPlay() override;
};