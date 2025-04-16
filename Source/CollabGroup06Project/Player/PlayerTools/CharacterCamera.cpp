#include "CharacterCamera.h"

#include "CollabGroup06Project/Creatures/Creature_Base.h"
#include "CollabGroup06Project/Player/PlayerCharacter.h"
#include "CollabGroup06Project/UIWidgets/DispalyScreenshots.h"
#include "CollabGroup06Project/UIWidgets/UI_Journal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetRenderingLibrary.h"

ACharacterCamera::ACharacterCamera()
{
}

void ACharacterCamera::ToggleCamera_Implementation(APlayerCharacter* player)
{
	
	_CameraOpen = !_CameraOpen;
	if (_CameraOpen)
	{
		//Event fired to player to resolve
		//HideHelpPanel();
		if (ScreenshotWidgetInstance)
		{
			ScreenshotWidgetInstance->SetVisibility(ESlateVisibility::Visible);
		}
		FVector CurrentLocation = player->_CameraSpringArmComponent->GetRelativeLocation();
		CurrentLocation.Z =+ 200.0f;
		
		player->_CameraSpringArmComponent->TargetArmLength = player->_CameraArmLengthCam;
		player->_CameraSpringArmComponent->SetRelativeLocation(CurrentLocation);
		FVector NewLocation = GetActorLocation();
		player->PreviousLocation = GetActorLocation();
		NewLocation.Z =+ 195.0f;
		SetActorLocation(NewLocation);
	}
	else
	{
		FVector CurrentLocation = FVector(0.0f, 0.0f, 0.0f);
		
		player->_CameraSpringArmComponent->TargetArmLength = player->_CameraArmLengthDef;
		player->_CameraSpringArmComponent->SetRelativeLocation(CurrentLocation);
		SetActorLocation(player->PreviousLocation);
		if (ScreenshotWidgetInstance)
		{
			ScreenshotWidgetInstance->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	
}

void ACharacterCamera::TakePhoto_Implementation(APlayerCharacter* player,  UUserWidget* journal)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Green, FString::Printf(TEXT("Works")));

	if(_CameraOpen)
	{
		IsAnythingInCameraView(GetWorld(), player);
	}
	else
	{
		//HideHelpPanel();
		if (journal->GetVisibility() == ESlateVisibility::Visible)
		{
			APlayerController* PC = UGameplayStatics::GetPlayerController(player, 0);
			if (PC)
			{
				PC->bShowMouseCursor = false;

				//set input mode to UI
				FInputModeGameOnly InputMode;
				

				PC->SetInputMode(InputMode);
			}
			
			journal->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			APlayerController* PC = UGameplayStatics::GetPlayerController(player, 0);
			if (PC)
			{
				PC->bShowMouseCursor = true;

				//set input mode to UI
				FInputModeGameAndUI InputMode;
				InputMode.SetWidgetToFocus((journal->TakeWidget()));
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

				PC->SetInputMode(InputMode);
			}
			
			journal->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

bool ACharacterCamera::IsAnythingInCameraView(UWorld* world, APlayerCharacter* player)
{
	if (!world) return false;
	FVector Start = GetActorLocation();
	FVector ForwardVector = player->_ThirdPersonCameraComponent->GetForwardVector();
	float TraceDistance = player->_PhotographDistance;
	FVector End = Start + (ForwardVector * TraceDistance);

	float SphereRadius = player->_PhotographDistance;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	
	TArray<FHitResult> HitResults;

	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults, Start, End, FQuat::Identity, ECC_Visibility,
		FCollisionShape::MakeSphere(SphereRadius), TraceParams
		);
	
	CaptureScreenshot();
	
	for (const FHitResult& Hit : HitResults)
	{
		if (Hit.GetActor())
		{
			if (!Hit.GetActor()->WasRecentlyRendered()) continue;
			if (!Hit.GetActor()->ActorHasTag("Scannable")) continue;
			
			GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Green, FString::Printf(TEXT("Actor in view: %s"), *Hit.GetActor()->GetName()));

			//Need reference to the animals photograph status
			ACreature_Base* animal = Cast<ACreature_Base>(Hit.GetActor());
			GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Green, FString::Printf(TEXT("Photo stat: %hhd"), animal->_IsPhotographable));

			FString Tag;
		
			if (Hit.GetActor()->ActorHasTag("Deer"))
			{
				Tag = "Deer";
			}
			else if (Hit.GetActor()->ActorHasTag("Lizard"))
			{
				Tag = "Lizard";
			}
			else if (Hit.GetActor()->ActorHasTag("Snail"))
			{
				Tag = "Snail";
			}
			else if (Hit.GetActor()->ActorHasTag("BerryBird"))
			{
				Tag = "BerryBird";
			}
			else if (Hit.GetActor()->ActorHasTag("GroundCreature"))
			{
				Tag = "GroundCreature";
			}
			else if (Hit.GetActor()->ActorHasTag("LargeCreature"))
			{
				Tag = "LargeCreature";
			}
			else if (Hit.GetActor()->ActorHasTag("RockCreature"))
			{
				Tag = "RockCreature";
			}
			else if (Hit.GetActor()->ActorHasTag("Beetle"))
			{
				Tag = "Beetle";
			}
			else
			{
				Tag = "Error : Creature Tag not set";
				GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Red, FString::Printf(TEXT("Error : Creature Tag not set")));
			}

			_UpdateUIDelayDelegate.BindUFunction(this, FName("UpdateUI"), Tag, animal);
			GetWorld()->GetTimerManager().SetTimer(_UpdateUIDelayTimer, _UpdateUIDelayDelegate, 0.1f, false);

			return true;
		}
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Green, FString::Printf(TEXT("Nothing in view")));
	UE_LOG(LogTemp, Warning, TEXT("Nothing in view"));

	return false;
}

void ACharacterCamera::CaptureScreenshot()
{
	FString ScreenshotName = FPaths::ProjectSavedDir() + TEXT("Screenshots/Screenshot1.png");
	FScreenshotRequest::RequestScreenshot(ScreenshotName, false, false);
	UE_LOG(LogTemp, Warning, TEXT("Screenshot Captured: %s"), *ScreenshotName);
}

void ACharacterCamera::BeginPlay()
{
	Super::BeginPlay();
}
