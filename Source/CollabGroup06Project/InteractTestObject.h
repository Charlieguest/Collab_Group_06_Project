// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollabGroup06Project/Interfaces/Interact.h"
#include "InteractTestObject.generated.h"

UCLASS()
class COLLABGROUP06PROJECT_API AInteractTestObject : public AActor, public IInteract
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractTestObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	virtual void interact_Implementation() override;
};
