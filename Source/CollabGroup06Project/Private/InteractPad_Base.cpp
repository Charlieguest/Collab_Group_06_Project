// Fill out your copyright notice in the Description page of Project Settings.


#include "CollabGroup06Project/Public/InteractPad_Base.h"

// Sets default values
AInteractPad_Base::AInteractPad_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractPad_Base::BeginPlay()
{
	Super::BeginPlay();
	
}


void AInteractPad_Base::PadActive_Implementation()
{
	IPadInteractable::PadActive_Implementation();
	switch (isActive)
	{
	case true:
		isActive = false;
		break;
	case false:
		isActive = true;
		break;
	}
}

void AInteractPad_Base::OnOverlapBeginBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AInteractPad_Base::OnOverlapEndBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


