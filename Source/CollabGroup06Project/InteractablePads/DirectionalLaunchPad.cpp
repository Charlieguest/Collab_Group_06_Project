// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionalLaunchPad.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ADirectionalLaunchPad::ADirectionalLaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADirectionalLaunchPad::BeginPlay()
{
	Super::BeginPlay();
	_CollisionComp = GetComponentByClass<UBoxComponent>();
	_ArrowComp = GetComponentByClass<UArrowComponent>();
	_CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ADirectionalLaunchPad::ADirectionalLaunchPad::OnOverlapBeginBox);
}

// Called every frame
void ADirectionalLaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ADirectionalLaunchPad::OnOverlapBeginBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OtherCharacter != nullptr)
	{
		FVector LaunchVelocity = _ArrowComp->GetForwardVector() * M_LaunchVelocity;
		OtherCharacter->LaunchCharacter(FVector(LaunchVelocity) , XYOverride, ZOverride);
	}
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.f, FColor::Red, *FString::Printf(TEXT("On Component Overlap Begin!")));
}

