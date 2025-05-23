// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "InteractPad_Base.h"
#include "GaseousPlant.generated.h"

UCLASS()
class COLLABGROUP06PROJECT_API AGaseousPlant : public AInteractPad_Base
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGaseousPlant();
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Timer") float _timer = 1.0f;
	UPROPERTY(EditInstanceOnly, Category = "Player forces") float _velocity = 800;
	UPROPERTY(EditInstanceOnly, Category="Player forces") bool XYOverride = true;
	UPROPERTY(EditInstanceOnly, Category="Player forces") bool ZOverride = true;
	UPROPERTY(EditInstanceOnly, Category = "Player forces") bool TimerStarted = false;
	UPROPERTY(EditInstanceOnly, Category = "Player forces") bool IsGaseousActive = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//FTimerManager& _TimerManager = GetWorldTimerManager();
	FTimerHandle _TimerHandle;
public:	
	UFUNCTION()
	virtual void OnOverlapBeginBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	UFUNCTION()
	virtual void OnOverlapEndBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
	virtual void PadActive_Implementation() override;
	
	UFUNCTION()
	void ActiveSwitches();
};
