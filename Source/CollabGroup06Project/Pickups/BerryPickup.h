#pragma once

#include "CoreMinimal.h"
#include "CollabGroup06Project/Interfaces/Interact.h"
#include "GameFramework/Actor.h"
#include "BerryPickup.generated.h"

class USphereComponent;

UCLASS()
class COLLABGROUP06PROJECT_API ABerryPickup : public AActor, public IInteract
{
	GENERATED_BODY()

public:
	ABerryPickup();

	virtual void interact_Implementation() override;
	
	void PulltoPlayerPos(FVector playerPos);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> _CollisionComponent;
	
protected:
	virtual void BeginPlay() override;
	
};