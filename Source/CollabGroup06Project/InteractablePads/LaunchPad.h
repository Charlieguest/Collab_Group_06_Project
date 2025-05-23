// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractPad_Base.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "LaunchPad.generated.h"



UCLASS()
class COLLABGROUP06PROJECT_API ALaunchPad : public AInteractPad_Base
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/*UPROPERTY(EditAnywhere, Category="Collider Object") TObjectPtr<UBoxComponent> _CollisionComp;;*/
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Launch Velocity") int32 M_LaunchVelocity = 750;
	//Positional overrides for the launching of the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Position Override") bool XYOverride = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Position Override") bool ZOverride = true;
public:	
	UFUNCTION()
	virtual void PadActive_Implementation() override;
	UFUNCTION()
	virtual void OnOverlapBeginBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnOverlapEndBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
	
};
