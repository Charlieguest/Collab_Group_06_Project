// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"



// Sets default values
ALaunchPad::ALaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isActive = true;
}

// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();
	_CollisionComp = GetComponentByClass<UBoxComponent>();
	_CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::ALaunchPad::OnOverlapBeginBox);
	
}

void ALaunchPad::PadActive_Implementation()
{
	Super::PadActive_Implementation();
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

void ALaunchPad::OnOverlapBeginBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (isActive)
	{
		ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
		if (OtherCharacter != nullptr)
		{
			OtherCharacter->LaunchCharacter(FVector(0,0,M_LaunchVelocity), XYOverride, ZOverride);
		}
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.f, FColor::Red, *FString::Printf(TEXT("On Component Overlap Begin!")));
	}
}

void ALaunchPad::OnOverlapEndBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

