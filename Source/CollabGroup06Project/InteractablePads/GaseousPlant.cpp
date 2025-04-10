// Fill out your copyright notice in the Description page of Project Settings.


#include "GaseousPlant.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AGaseousPlant::AGaseousPlant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AGaseousPlant::BeginPlay()
{
	Super::BeginPlay();
	isActive = false;
	_CollisionComp = GetComponentByClass<UBoxComponent>();
	_CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AGaseousPlant::AGaseousPlant::OnOverlapBeginBox);
	_CollisionComp->OnComponentEndOverlap.AddDynamic(this, &AGaseousPlant::AGaseousPlant::OnOverlapEndBox);
}

void AGaseousPlant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isActive == true)
	{
		if (TimerStarted == false)
		{
			TimerStarted = true;
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Timer started");
			}
			if (GetWorld())
			{
				GetWorld()->GetTimerManager().SetTimer(_TimerHandle, this, &AGaseousPlant::PadActive_Implementation, _timer, false);
				
			}
		}
	}
	
}

// Called every frame


void AGaseousPlant::PadActive_Implementation()
{
	Super::PadActive_Implementation();
	switch (isActive)
	{
	case true:
		isActive = true;
		break;
	case false:
		isActive = false;
		TimerStarted = false;
		break;
	}
}

void AGaseousPlant::OnOverlapBeginBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OtherCharacter != nullptr)
	{
		if (isActive)
		{
			OtherCharacter->LaunchCharacter(FVector(0,0,100), XYOverride, ZOverride);
			OtherCharacter->GetCharacterMovement()->GravityScale = -0.50;
			OtherCharacter->GetVelocity().Set(0,0,100.0);
		}
		
	}
}


void AGaseousPlant::OnOverlapEndBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (isActive)
	{
		ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
		if (OtherCharacter != nullptr)
		{
			OtherCharacter->GetCharacterMovement()->GravityScale = 1.75;
		}
	}
	
}






