// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractTestObject.h"


// Sets default values
AInteractTestObject::AInteractTestObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInteractTestObject::BeginPlay()
{
	Super::BeginPlay();
	
}

 void AInteractTestObject::interact_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("interact ran"));
}


