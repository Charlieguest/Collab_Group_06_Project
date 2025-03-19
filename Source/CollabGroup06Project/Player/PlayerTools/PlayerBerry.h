#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerBerry.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class COLLABGROUP06PROJECT_API APlayerBerry : public AActor
{
	GENERATED_BODY()

public:
	APlayerBerry();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USphereComponent> _Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UStaticMeshComponent> _AttachedBerryMesh;
	
protected:
	virtual void BeginPlay() override;

};
