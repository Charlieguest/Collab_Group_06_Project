// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Public/InteractPad_Base.h"
#include "GaseousPlant.generated.h"

UCLASS()
class COLLABGROUP06PROJECT_API AGaseousPlant : public AInteractPad_Base
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGaseousPlant();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category="Position Override") bool XYOverride = true;
	UPROPERTY(EditAnywhere, Category="Position Override") bool ZOverride = true;
public:	

	virtual void PadActive_Implementation() override;

	UFUNCTION()
	virtual void OnOverlapBeginBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	UFUNCTION()
	virtual void OnOverlapEndBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	void Timer();
};
