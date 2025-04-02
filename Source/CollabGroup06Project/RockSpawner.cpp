// Fill out your copyright notice in the Description page of Project Settings.


#include "RockSpawner.h"

#include "Components/BoxComponent.h"

// Sets default values
ARockSpawner::ARockSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

}

// Called when the game starts or when spawned
void ARockSpawner::BeginPlay()
{
	Super::BeginPlay();
	_CollisionComp = GetComponentByClass<UBoxComponent>();
	SpawnChosenActor();
}

// Called every frame
void ARockSpawner::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);

}



void ARockSpawner::SpawnChosenActor_Implementation()
{
	for (int i = 0; i < iterations; i++)
	{
		FVector location = _CollisionComp->GetComponentLocation();
		FVector Extent = _CollisionComp->GetScaledBoxExtent();
		FVector RandPoint = location + FMath::RandRange(-Extent.Size(), Extent.Size());
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnClass.Get(),RandPoint, GetActorRotation(), SpawnParams);
	}
}


