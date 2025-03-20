// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractTestObject.h"


AInteractTestObject::AInteractTestObject()
{

}


void AInteractTestObject::BeginPlay()
{
	Super::BeginPlay();
	
}

 void AInteractTestObject::interact_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("interact ran"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Works")));
}


