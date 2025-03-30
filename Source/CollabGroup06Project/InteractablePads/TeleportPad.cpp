#include "TeleportPad.h"

ATeleportPad::ATeleportPad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATeleportPad::BeginPlay()
{
	Super::BeginPlay();
	_CollisionComp = GetComponentByClass<UBoxComponent>();
	_CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ATeleportPad::ATeleportPad::OnOverlapBeginBox);
}

void ATeleportPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATeleportPad::OnOverlapBeginBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OtherCharacter != nullptr)
	{
		
		if (M_LinkedTeleportPad != nullptr)
		{
			//prevent character movement until teleported / animation is done 

			//call other teleporter to start delay 
			M_LinkedTeleportPad->ActivateDelay();

			//teleport character to the teleporter pad
		}
	}
}

void ATeleportPad::ActivateDelay()
{


}
