#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Player/PlayerTools/ItemData.h"
#include "InventoryItem.generated.h"

UCLASS()
class COLLABGROUP06PROJECT_API AInventoryItem : public AActor
{
	GENERATED_BODY()

public:
	AInventoryItem();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _ItemMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> _Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Inventory Item Properties", meta=(ExposeOnSpawn=true))
	FItemData _ItemData;

protected:
	virtual void BeginPlay() override;
};
