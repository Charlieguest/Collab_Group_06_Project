﻿#include "CharacterTool_Camera.h"

#include "CollabGroup06Project/Creatures/Creature_Base.h"
#include "CollabGroup06Project/Player/PlayerCharacter.h"
#include "CollabGroup06Project/UIWidgets/DispalyScreenshots.h"
#include "CollabGroup06Project/UIWidgets/UI_Journal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetRenderingLibrary.h"

ACharacterTool_Camera::ACharacterTool_Camera()
{
}

void ACharacterTool_Camera::BeginPlay()
{
	Super::BeginPlay();

	if (ScreenshotClass)
	{
		ScreenshotWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), ScreenshotClass);
		ScreenshotWidgetInstance->AddToViewport();
		ScreenshotWidgetInstance->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ACharacterTool_Camera::ToggleCamera_Implementation(APlayerCharacter* player)
{
	
	_CameraOpen = !_CameraOpen;
	OnHoldingCamera.Broadcast(_CameraOpen);
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

void ACharacterTool_Camera::TakePhoto_Implementation(APlayerCharacter* player,  UUserWidget* journal)
{
	if(_CameraOpen)
	{
		IsAnythingInCameraView(GetWorld(), player);
	}
}

bool ACharacterTool_Camera::IsAnythingInCameraView(UWorld* world, APlayerCharacter* player)
{
	if (!world) return false;
	FVector Start = player->GetActorLocation();
	FVector ForwardVector = player->_ThirdPersonCameraComponent->GetForwardVector();
	float TraceDistance = player->_PhotographDistance;
	FVector End = Start + (ForwardVector * TraceDistance);

	float SphereRadius = player->_PhotographDistance;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(player);
	
	TArray<FHitResult> HitResults;

	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults, Start, End, FQuat::Identity, ECC_Visibility,
		FCollisionShape::MakeSphere(SphereRadius), TraceParams
		);
	
	CaptureScreenshot();
	
	for (const FHitResult& Hit : HitResults)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Purple, FString::Printf(TEXT("Actor in view: %s"), *Hit.GetActor()->GetName()));

		if (Hit.GetActor())
		{
			if (!Hit.GetActor()->WasRecentlyRendered()) continue;
			if (!Hit.GetActor()->ActorHasTag("Scannable")) continue;
			
			//GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Green, FString::Printf(TEXT("Actor in view: %s"), *Hit.GetActor()->GetName()));

			//Need reference to the animals photograph status
			ACreature_Base* animal = Cast<ACreature_Base>(Hit.GetActor());
			//->AddOnScreenDebugMessage(-1, 1.2f, FColor::Green, FString::Printf(TEXT("Photo stat: %hhd"), animal->_IsPhotographable));

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
				//GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Red, FString::Printf(TEXT("Error : Creature Tag not set")));
			}

			_UpdateUIDelayDelegate.BindUFunction(this, FName("UpdateUIOnPlayer"), Tag, animal);
			GetWorld()->GetTimerManager().SetTimer(_UpdateUIDelayTimer, _UpdateUIDelayDelegate, 0.1f, false);

			return true;
		}
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Green, FString::Printf(TEXT("Nothing in view")));
	UE_LOG(LogTemp, Warning, TEXT("Nothing in view"));

	return false;
}

void ACharacterTool_Camera::UpdateUIOnPlayer(FString animalType, ACreature_Base* animal)
{
	OnSuccessfulAnimalPhotoTaken.Broadcast(animalType, animal, ScreenshotWidgetInstance);
}

void ACharacterTool_Camera::CaptureScreenshot()
{
	FString ScreenshotName = FPaths::ProjectSavedDir() + TEXT("Screenshots/Screenshot1.png");
	FScreenshotRequest::RequestScreenshot(ScreenshotName, false, false);
	UE_LOG(LogTemp, Warning, TEXT("Screenshot Captured: %s"), *ScreenshotName);
}

