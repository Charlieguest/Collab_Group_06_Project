// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractPad_Base.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "DirectionalLaunchPad.generated.h"

UCLASS()
class COLLABGROUP06PROJECT_API ADirectionalLaunchPad : public AInteractPad_Base
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADirectionalLaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// UPROPERTY(EditAnywhere, Category="Collider Object") UBoxComponent* Collider;
	// UPROPERTY(EditAnywhere, Category="Collider Object") UArrowComponent* Arrow;
	UPROPERTY(EditAnywhere, Category="Launch Velocity") int32 M_LaunchVelocity = 1000;
	UPROPERTY(EditAnywhere, Category="Position Override") bool XYOverride = true;
	UPROPERTY(EditAnywhere, Category="Position Override") bool ZOverride = true;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	virtual void OnOverlapBeginBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
};
