#include "TeleportPad.h"

#include "Compression/lz4hc.h"

ATeleportPad::ATeleportPad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

ATeleportPad::~ATeleportPad()
{
	M_character = nullptr;
}

void ATeleportPad::BeginPlay()
{
	Super::BeginPlay();
	_CollisionComp = GetComponentByClass<UBoxComponent>();
	_CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ATeleportPad::ATeleportPad::OnOverlapBeginBox);

	_ArrowComp = GetComponentByClass<UArrowComponent>();
}

void ATeleportPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATeleportPad::OnOverlapBeginBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	M_character = Cast<ACharacter>(OtherActor);
	if (M_character != nullptr)
	{
		//is active? if player enters collision due to teleporting to this pad it will ignore them until they enter the pad again
		if (!M_IsTeleportActive)
		{
			M_IsTeleportActive = true;
			return;
		}
		
		if (M_LinkedTeleportPad != nullptr)
		{
			//prevent character movement until teleported / animation is done 

			//call other teleporter to de-activate until re-entered 
			M_LinkedTeleportPad->ActivateDelay();

			//teleport character to the teleporter pad
			TeleportPlayer();
		}
	}
}

void ATeleportPad::ActivateDelay()
{
	M_IsTeleportActive = false;
	M_LinkedTeleportPad->M_IsTeleportActive = false;
}


void ATeleportPad::TeleportPlayer()
{
	M_character->TeleportTo(M_LinkedTeleportPad->_ArrowComp->GetComponentLocation(), M_LinkedTeleportPad->_ArrowComp->GetComponentRotation());
}
