// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollabGroup06Project/Interfaces/PadInteractable.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"

#include "InteractPad_Base.generated.h"

UCLASS(Abstract)
class COLLABGROUP06PROJECT_API AInteractPad_Base : public AActor, public IPadInteractable
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	AInteractPad_Base();
	bool isActive = true;
	TObjectPtr<UBoxComponent> _CollisionComp;
	TObjectPtr<UArrowComponent> _ArrowComp;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame

	
	virtual void PadActive_Implementation() override;

	virtual void OnOverlapBeginBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	virtual void OnOverlapEndBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
