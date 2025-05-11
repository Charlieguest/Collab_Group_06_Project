#include "GaseousPlant.h"

#include "CollabGroup06Project/Projectiles/GrappleProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AGaseousPlant::AGaseousPlant()
{
	PrimaryActorTick.bCanEverTick = true;

	_GrappleCollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
	//_GrappleCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AGaseousPlant::OnGrappleOverlapBegin);
	//_GrappleCollisionComp->OnComponentEndOverlap.AddDynamic(this, &AGaseousPlant::OnGrappleOverlapEnd);

}

void AGaseousPlant::BeginPlay()
{
	Super::BeginPlay();
	isActive = false;
	TimerStarted = false;
	_CollisionComp = GetComponentByClass<UBoxComponent>();
	_CollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
	_CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AGaseousPlant::AGaseousPlant::OnOverlapBeginBox);
	_CollisionComp->OnComponentEndOverlap.AddDynamic(this, &AGaseousPlant::AGaseousPlant::OnOverlapEndBox);
}

void AGaseousPlant::OnOverlapBeginBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	
	if (IsGaseousActive)
	{
		XYOverride = true;
		ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
		if (OtherCharacter != nullptr)
		{

			OtherCharacter->LaunchCharacter(FVector(0,0,_velocity), XYOverride, ZOverride);
			OtherCharacter->GetCharacterMovement()->GravityScale = -0.50;
			OtherCharacter->GetVelocity().Set(0,0,100.0);
		}
	}
}


void AGaseousPlant::OnOverlapEndBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	XYOverride = false;
	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OtherCharacter != nullptr)
	{
		OtherCharacter->GetCharacterMovement()->GravityScale = 1.75;
	}
	
}

void AGaseousPlant::PadActive_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "sTART Chain");
	if(!IsGaseousActive)
 	{
		CompletePlantAction();

		
 		GetWorld()->GetTimerManager().SetTimer(_TimerHandle, this, &AGaseousPlant::ActiveSwitches, _timer, false);
		IsGaseousActive = true;
 	}
}

void AGaseousPlant::ActiveSwitches()
{
	PlantActionEnd();

	IsGaseousActive = false;
}






