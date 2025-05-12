#include "CharacterTool_Scanner.h"

#include "CharacterTool_GrappleGun.h"
#include "CollabGroup06Project/Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


ACharacterTool_Scanner::ACharacterTool_Scanner()
{
}

void ACharacterTool_Scanner::Scan_Implementation(APlayerCharacter* player)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Red, FString::Printf(TEXT("SCANNING")));
	
	if(!player->_IsScanning &&
		!player->_HasFired  /*&&
		!player->_SpawnedGrappleGun->_IsGrapplingPlayer &&
		!player->_SpawnedGrappleGun->_IsGrapplingBerry */)
	{
		player->_IsScanning = true;
		BeginScan();

		//Stopping player movement
		player->GetCharacterMovement()->MaxWalkSpeed = 0.0f;


		//Broadcast event to start player movement again
		GetWorld()->GetTimerManager().SetTimer(_PerformScanTimerHandle, this, &ACharacterTool_Scanner::ReleasePlayer, _ScanTime, false);
		
		FVector Start = GetActorLocation();
		FVector ForwardVector = player->_ThirdPersonCameraComponent->GetForwardVector();
		float TraceDistance = player->_ScanDistance;
		FVector End = Start + (ForwardVector * TraceDistance);

		float SphereRadius = player->_ScanDistance;
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
	
		TArray<FHitResult> HitResults;

		bool bHit = GetWorld()->SweepMultiByChannel(
			HitResults, Start, End, FQuat::Identity, ECC_Visibility,
			FCollisionShape::MakeSphere(SphereRadius), TraceParams
			);

		for (const FHitResult& Hit : HitResults)
		{
			if (Hit.GetActor())
			{
				if (!Hit.GetActor()->WasRecentlyRendered()) continue;
				if (!Hit.GetActor()->ActorHasTag("Scannable")) continue;

				AActor* Actor = Hit.GetActor();

				FVector Origin;
				FVector Extent;
				Actor->GetActorBounds(true, Origin, Extent);

				// Firing Interface in blueprint
				player->_Animal = Actor;
				// Execute interface on each rendered actor
				player->ActivateAnimal();
			
				GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Red, FString::Printf(TEXT("Actor in view: %s"), *Actor->GetName()));
			}
		}
	}
}

void ACharacterTool_Scanner::BeginScan_Implementation()
{
}

void ACharacterTool_Scanner::ReleasePlayer()
{
	OnReleasePlayer.Broadcast();
}

void ACharacterTool_Scanner::BeginPlay()
{
	Super::BeginPlay();
}
