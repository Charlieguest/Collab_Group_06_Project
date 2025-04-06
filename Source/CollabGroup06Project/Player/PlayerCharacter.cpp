#include "PlayerCharacter.h"

#include <string>

#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "CollabGroup06Project/Interfaces/Interact.h"
#include "CollabGroup06Project/Pickups/BerryPickup.h"
#include "Components/CapsuleComponent.h"
#include "CollabGroup06Project/Player/PlayerTools/GrappleGun.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "DrawDebugHelpers.h"
#include "CollabGroup06Project/UIWidgets/DispalyScreenshots.h"
#include "Components/SphereComponent.h"
#include "EngineUtils.h"
#include "CollabGroup06Project/Creatures/Creature_Base.h"
#include "CollabGroup06Project/UIWidgets/UI_Journal.h"
#include "CollabGroup06Project/Pickups/InventoryItem.h"


APlayerCharacter::APlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);

	_CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	_CameraSpringArmComponent->SetupAttachment(RootComponent);
	_CameraSpringArmComponent->bUsePawnControlRotation = true;
	
	_ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
	_ThirdPersonCameraComponent->SetupAttachment(_CameraSpringArmComponent);

	_InteractionZoneSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionZone"));
	_InteractionZoneSphereComponent->SetupAttachment(_CameraSpringArmComponent);
	_InteractionZoneSphereComponent->AddLocalOffset(_InteractZoneOffset);
	_InteractionZoneSphereComponent->InitSphereRadius(110);
	_InteractionZoneSphereComponent->SetGenerateOverlapEvents(true);
	_InteractionZoneSphereComponent->SetCollisionProfileName(TEXT("OverlapAll"), false);

	_GrappleAttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("GrappleAttachPoint"));
	_GrappleAttachPoint->SetupAttachment(GetRootComponent());

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (ScreenshotClass)
	{
		ScreenshotWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), ScreenshotClass);
		ScreenshotWidgetInstance->AddToViewport();
		ScreenshotWidgetInstance->SetVisibility(ESlateVisibility::Collapsed);
		
	}

	if (UIJournalClass)
    	{
    		UIJournalInstance = CreateWidget<UUserWidget>(GetWorld(), UIJournalClass);
			UIJournalInstance->AddToViewport();
			UIJournalInstance->SetVisibility(ESlateVisibility::Collapsed);
    	}

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = this;

	AActor* grappleGun = GetWorld()->SpawnActor(_GrappleGun, &_GrappleAttachPoint->GetComponentTransform(), spawnParams);
	grappleGun->AttachToComponent(_GrappleAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);

	_SpawnedGrappleGun = Cast<AGrappleGun>(grappleGun);
	_SpawnedGrappleGun->OnGrappleStart.AddDynamic(this, &APlayerCharacter::GrappleStart);
	_SpawnedGrappleGun->OnGrappleDuring.AddDynamic(this, &APlayerCharacter::GrappleDuring);
	_SpawnedGrappleGun->OnGrappleEnd.AddDynamic(this, &APlayerCharacter::GrappleEnd);
}


void APlayerCharacter::Move_Implementation(const FInputActionValue& Instance)
{
	if (!bToggleInput || !bIsCameraOpen)
	{	
		if(Controller != nullptr)
		{
			const FVector2d MoveValue = Instance.Get<FVector2d>();
			MovementRotation =  FRotator(0, Controller->GetControlRotation().Yaw, 0);

			if(MoveValue.Y != 0.0f && GetCharacterMovement()->MaxWalkSpeed > 0)
			{
					const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);
					AddMovementInput(Direction, MoveValue.Y);
					GetCapsuleComponent()->SetWorldRotation(MovementRotation);
			}

			if(MoveValue.X != 0.0f && GetCharacterMovement()->MaxWalkSpeed > 0)
			{
					const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);
					AddMovementInput(Direction, MoveValue.X);
					GetCapsuleComponent()->SetWorldRotation(MovementRotation);
			}
		}
	}
	
}

void APlayerCharacter::Look_Implementation(const FInputActionValue& Instance)
{
		if(Controller != nullptr)
		{
			const FVector2d AxisValue = Instance.Get<FVector2d>();

			if(AxisValue.Y != 0.0f)
			{
				AddControllerPitchInput(AxisValue.Y);
			}

			if(AxisValue.X != 0.0f)
			{
				AddControllerYawInput(AxisValue.X);
			}
		}
	
}

void APlayerCharacter::Jump_Implementation(const FInputActionValue& Instance)
{
	if (bIsCameraOpen)
	{
		
	}
	else
	{
		Super::Jump();
	}
}

void APlayerCharacter::ToggleInventory_Implementation(const FInputActionValue& Intance)
{
	//Executing Blueprint Functionality
	InventoryBPAction();
}

void APlayerCharacter::ToggleCamera_Implementation(const FInputActionValue& Instance)
{
	bIsCameraOpen = !bIsCameraOpen;
	if (bIsCameraOpen)
	{
		HideHelpPanel();
		if (ScreenshotWidgetInstance)
		{
			ScreenshotWidgetInstance->SetVisibility(ESlateVisibility::Visible);
		}
		FVector CurrentLocation = _CameraSpringArmComponent->GetRelativeLocation();
		CurrentLocation.Z =+ 200.0f;
		
		_CameraSpringArmComponent->TargetArmLength = _CameraArmLengthCam;
		_CameraSpringArmComponent->SetRelativeLocation(CurrentLocation);
		FVector NewLocation = GetActorLocation();
		PreviousLocation = GetActorLocation();
		NewLocation.Z =+ 195.0f;
		SetActorLocation(NewLocation);
	}
	else
	{
		FVector CurrentLocation = FVector(0.0f, 0.0f, 0.0f);
		
		_CameraSpringArmComponent->TargetArmLength = _CameraArmLengthDef;
		_CameraSpringArmComponent->SetRelativeLocation(CurrentLocation);
		SetActorLocation(PreviousLocation);
		if (ScreenshotWidgetInstance)
		{
			ScreenshotWidgetInstance->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void APlayerCharacter::TakePhoto_Implementation(const FInputActionValue& Instance)
{
	if(bIsCameraOpen)
	{
	  isAnythingInCameraView(GetWorld());
	}
	else
	{
		if (UIJournalInstance->GetVisibility() == ESlateVisibility::Visible)
		{
			UIJournalInstance->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			UIJournalInstance->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void APlayerCharacter::Scan_Implementation(const FInputActionValue& Instance)
{
	IInputActionable::Scan_Implementation(Instance);

	GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Red, FString::Printf(TEXT("SCANNING")));
	
	if(!_IsScanning &&
		!_HasFired &&
		!_SpawnedGrappleGun->_IsGrapplingPlayer &&
		!_SpawnedGrappleGun->_IsGrapplingBerry)
	{
		_IsScanning = true;

		//TODO: Stop Player Movement
		GetCharacterMovement()->MaxWalkSpeed = 0.0f;
		//TODO: Set Off A Timer To Start Player Movement

		GetWorld()->GetTimerManager().SetTimer(_PerformScanTimerHandle, this, &APlayerCharacter::ReleasePlayer, 2.0f, false);

		//TODO: Do frustum scan

		//Repeated Code -- once this is complete work out a way call the same function, maybe with the boundaries passed as params
		
		FVector ViewLocation = _ThirdPersonCameraComponent->GetRelativeLocation();
		FRotator ViewRotation = _ThirdPersonCameraComponent->GetRelativeRotation();

		FMatrix ViewMatrix = FInverseRotationMatrix(ViewRotation) *FTranslationMatrix(-ViewLocation);
		float FOV = _ThirdPersonCameraComponent->FieldOfView;

		//Create projection matrix
		const float AspectRatio = 16.0f / 9.0f;
		const float NearPlane = GNearClippingPlane;
		const float FarPlane = 10000.f;

		FMatrix ProjectionMatrix = FReversedZPerspectiveMatrix
			(FOV * (float)PI / 360.0f, //degrees to radians
			AspectRatio,
			NearPlane,
			FarPlane);

		FConvexVolume Frustrum;
		GetViewFrustumBounds(Frustrum, ViewMatrix * ProjectionMatrix, false);

		for (TActorIterator<AActor> It(GetWorld()); It; ++It)
		{
			AActor* Actor = *It;
			if (!Actor->WasRecentlyRendered()) continue;
			if (!Actor || Actor == _ThirdPersonCameraComponent->GetOwner()) continue;
			if (!Actor->ActorHasTag("Scannable")) continue;
			

			FVector Origin;
			FVector Extent;
			Actor->GetActorBounds(true, Origin, Extent);
			//DrawDebugLine(GetWorld(), Origin, Extent, FColor::Magenta, false, 5, 0, 5);

			// Firing Interface in blueprint
			_Animal = Actor;
			// Execute interface on each rendered actor
			ActivateAnimal();
			
			GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Red, FString::Printf(TEXT("Actor in view: %s"), *Actor->GetName()));
			
			if (Frustrum.IntersectBox(Origin, Extent))
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Green, FString::Printf(TEXT("Actor in view: %s"), *Actor->GetName()));
				
			}
		}

		//GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Green, FString::Printf(TEXT("Nothing in the view innit")));

		//TODO: Execute Interface on the animal if frustrum finds it
	}
}

void APlayerCharacter::ReleasePlayer()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	_IsScanning = false;
}


void APlayerCharacter::CaptureScreenshot()
{
	FString ScreenshotName = FPaths::ProjectSavedDir() + TEXT("Screenshots/Screenshot1.png");
	FScreenshotRequest::RequestScreenshot(ScreenshotName, false, false);
	UE_LOG(LogTemp, Warning, TEXT("Screenshot Captured: %s"), *ScreenshotName);
}

UTexture2D* APlayerCharacter::LoadScreenshotAsTexture()
{
	FString ScreenshotPath = FPaths::ProjectSavedDir() + TEXT("Screenshots/Screenshot1.png");
	
	if (!FPaths::FileExists(ScreenshotPath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Screenshot not found : %s"), *ScreenshotPath);
		return nullptr;
	}

	// Load image as texture
	UE_LOG(LogTemp, Warning, TEXT("Importing texture"));
	return UKismetRenderingLibrary::ImportFileAsTexture2D(this, ScreenshotPath);
}

void APlayerCharacter::UpdateUI(FString animalType, ACreature_Base* animal)
{
	if (ScreenshotWidgetInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Screenshot widget exists"));
		UDispalyScreenshots* TestUI = Cast<UDispalyScreenshots>(ScreenshotWidgetInstance);
		if (TestUI)
		{
			UTexture2D* ScreenshotTexture = LoadScreenshotAsTexture();
			UE_LOG(LogTemp, Warning, TEXT("Loading texture"));

			if (ScreenshotTexture)
			{
				UE_LOG(LogTemp, Warning, TEXT("Image being changed"));
				TestUI->SetImage(ScreenshotTexture);
			}
		}
	}

	if (UIJournalInstance && animal->_IsPhotographable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Screenshot widget exists"));
		UUI_Journal* Journal = Cast<UUI_Journal>(UIJournalInstance);
		if (Journal)
		{
			UTexture2D* ScreenshotTexture = LoadScreenshotAsTexture();
			animal->OnAnimalPhotographed.Broadcast();
			
			if (ScreenshotTexture)
			{
				if (animalType == TEXT("Deer"))
				{
					Journal->SetImage(Journal->Deer, ScreenshotTexture);
				}
				if (animalType == TEXT("Beetle"))
				{
					Journal->SetImage(Journal->Beetle, ScreenshotTexture);
				}
				if (animalType == TEXT("Lizard"))
				{
					Journal->SetImage(Journal->Lizard, ScreenshotTexture);
				}
				if (animalType == TEXT("Snail"))
				{
					Journal->SetImage(Journal->Snail, ScreenshotTexture);
				}
				if (animalType == TEXT("BerryBird"))
				{
					Journal->SetImage(Journal->BerryBird, ScreenshotTexture);
				}
				if (animalType == TEXT("GroundCreature"))
				{
					Journal->SetImage(Journal->GroundCreature, ScreenshotTexture);
				}
				if (animalType == TEXT("LargeCreature"))
				{
					Journal->SetImage(Journal->LargeCreature, ScreenshotTexture);
				}
				if (animalType == TEXT("RockCreature"))
				{
					Journal->SetImage(Journal->RockCreature, ScreenshotTexture);
				}
			}
		}
	}

	screenshotNum++;
}

bool APlayerCharacter::isAnythingInCameraView(UWorld* world)
{
	if (!world) return false;
	FVector Start = GetActorLocation();
	FVector ForwardVector =GetActorForwardVector();
	float TraceDistance = 500.0f;
	FVector End = Start + (ForwardVector * TraceDistance);

	float SphereRadius = 500.0f;
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
			
			GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Green, FString::Printf(TEXT("Actor in view: %s"), *Hit.GetActor()->GetName()));

			UE_LOG(LogTemp, Warning, TEXT("Actor in view: %s"), *Hit.GetActor()->GetName());

			//Need reference to the animals photograph status
			ACreature_Base* animal = Cast<ACreature_Base>(Hit.GetActor());
			GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Green, FString::Printf(TEXT("Photo stat: %hhd"), animal->_IsPhotographable));
		
			CaptureScreenshot();

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


void APlayerCharacter::PrimaryInteract_Implementation(const FInputActionValue& Instance)
{
	IInputActionable::PrimaryInteract_Implementation(Instance);
	MovementRotation =  FRotator(0, Controller->GetControlRotation().Yaw, 0);
	GetCapsuleComponent()->SetWorldRotation(MovementRotation);

	if(!_HasFired)
	{
		GetWorld()->GetTimerManager().SetTimer(_GrappleShootDelay, this, &APlayerCharacter::GrappleShoot, 0.01f, false);
		_HasFired = true;
	}
}

void APlayerCharacter::GrappleShoot()
{
	if(UKismetSystemLibrary::DoesImplementInterface(_SpawnedGrappleGun, UFireable::StaticClass()) )
	{
		bool hasFired = IFireable::Execute_Fire(_SpawnedGrappleGun, _ThirdPersonCameraComponent->GetForwardVector());
	}
}

void APlayerCharacter::CompletedPrimaryInteract_Implementation(const FInputActionValue& Instance)
{
	IInputActionable::CompletedPrimaryInteract_Implementation(Instance);
	
	if(UKismetSystemLibrary::DoesImplementInterface(_SpawnedGrappleGun, UFireable::StaticClass()) )
	{
		_HasFired = false;
		IFireable::Execute_Fire_Stop(_SpawnedGrappleGun);
	}
}

void APlayerCharacter::Interact_Implementation(const FInputActionValue& Instance)
{
	//check what is inside the interaction zone and if it implements the interface. if it does, call it
	TArray<AActor*> OverlappingActors;
	_InteractionZoneSphereComponent->GetOverlappingActors(OverlappingActors);
	for(int i = 0; i < OverlappingActors.Num(); i++)
		{
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *OverlappingActors[i]->GetName());
			if(UKismetSystemLibrary::DoesImplementInterface(OverlappingActors[i], UInteract::StaticClass()))
			{
				//if the interact interface is called on the player it crashes the editor
				if(OverlappingActors[i]->IsA(APlayerCharacter::StaticClass()))
				{
					continue;
				}

				// Checking if berry to attach berry to character
				if(OverlappingActors[i]->ActorHasTag("BerryPickup") && !_SpawnedGrappleGun->_HasBerry)
				{
					ABerryPickup* berryPickup = Cast<ABerryPickup>(OverlappingActors[i]);
					berryPickup->_OnPickedUp.AddUniqueDynamic(this, &APlayerCharacter::Pickup_Berry);
					IInteract::Execute_interact(OverlappingActors[i]);
					continue;
				}

				if(OverlappingActors[i]->ActorHasTag("InventoryItem"))
				{
					AInventoryItem* InventoryItem = Cast<AInventoryItem>(OverlappingActors[i]);
					PickUpInventoryItem(InventoryItem);
					IInteract::Execute_interact(OverlappingActors[i]);
					continue;
				}

				if(OverlappingActors[i]->ActorHasTag("Scannable"))
				{
					ACreature_Base* Creature = Cast<ACreature_Base>(OverlappingActors[i]);
					SearchInventory(*Creature->_RequiredItemName, true);

					if(_RequiredItemFound)
					{
						// Setting animal as "photographable" 
						IInteract::Execute_interact(OverlappingActors[i]);
					}
					continue;
				}
				

				//Not berry or inventory item but still interactable?
				//Execute Interact
				if(!OverlappingActors[i]->ActorHasTag("BerryPickup"))
				{
					IInteract::Execute_interact(OverlappingActors[i]);
				}
			}
		}
}

void APlayerCharacter::Pickup_Berry()
{
	//Spawning Berry on GrappleHook as visual reference
	_SpawnedGrappleGun->AttachBerry();
}

void APlayerCharacter::GrappleStart()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
}

void APlayerCharacter::GrappleDuring(FVector GrabPoint,  float grabForce)
{
	//GetCharacterMovement()->AddForce((GrabPoint - GetActorLocation()) * grabForce);
	
	GetCharacterMovement()->AddForce(FVector(
		(GrabPoint.X - GetActorLocation().X) * (grabForce * 1.5f),
		(GrabPoint.Y - GetActorLocation().Y) * (grabForce * 1.5f),
		(GrabPoint.Z - GetActorLocation().Z) * (grabForce / 2.5f)
		));
}

void APlayerCharacter::GrappleEnd()
{
	if (!GetCharacterMovement()->IsFalling())
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
	}
}

void APlayerCharacter::SearchInventory_Implementation(const FString& requiredItem, bool isInteracting)
{
}

void APlayerCharacter::PickUpInventoryItem_Implementation(AActor* interactItem)
{
}

void APlayerCharacter::InventoryBPAction_Implementation()
{
}

void APlayerCharacter::ActivateAnimal_Implementation()
{
}

void APlayerCharacter::HideHelpPanel_Implementation()
{
}

void APlayerCharacter::Init_Implementation()
{
}

