// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "RockSpawner.generated.h"

UCLASS()
class COLLABGROUP06PROJECT_API ARockSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	TObjectPtr<UBoxComponent> _CollisionComp;
	UPROPERTY(EditAnywhere, Category = "Spawner Settings")
	TSubclassOf<AActor> SpawnClass;
	UPROPERTY(EditAnywhere, Category = "Spawner Settings")
	int iterations = 0;
	
	
	// Sets default values for this actor's properties
	ARockSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SpawnChosenActor();
};
