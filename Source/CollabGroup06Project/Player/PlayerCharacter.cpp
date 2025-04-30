#include "PlayerCharacter.h"

#include <string>

#include "CableComponent.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "CollabGroup06Project/Interfaces/Interact.h"
#include "CollabGroup06Project/Pickups/BerryPickup.h"
#include "Components/CapsuleComponent.h"
#include "PlayerTools\CharacterTool_GrappleGun.h"
#include "PlayerTools\CharacterTool_Camera.h"
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
#include "Kismet/GameplayStatics.h"
#include "PlayerTools/CharacterTool_Scanner.h"


APlayerCharacter::APlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);
	// Set size for collision capsule
	
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
	_InteractionZoneSphereComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
	_GrappleAttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("GrappleAttachPoint"));
	_GrappleAttachPoint->SetupAttachment(GetRootComponent());

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	
}

void APlayerCharacter::BeginPlay()
{
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &APlayerCharacter::OnHit);
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

	AActor* currentTool = GetWorld()->SpawnActor(_GrappleGun, &_GrappleAttachPoint->GetComponentTransform(), spawnParams);
	currentTool->AttachToComponent(_GrappleAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
	
	_SpawnedCharacterTool = Cast<ACharacterTool_Base>(currentTool);
	_SpawnedCharacterTool->OnGrappleStart.AddDynamic(this, &APlayerCharacter::GrappleStart);
	_SpawnedCharacterTool->OnGrappleDuring.AddDynamic(this, &APlayerCharacter::GrappleDuring);
	_SpawnedCharacterTool->OnGrappleEnd.AddDynamic(this, &APlayerCharacter::GrappleEnd);
	_SpawnedCharacterTool->OnGrappleBerry.AddDynamic(this, &APlayerCharacter::ReleaseAim);
	 
}

void APlayerCharacter::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(UKismetSystemLibrary::DoesImplementInterface(OtherActor, UBerryAquireable::StaticClass()))
	{
		// Checking if berry to attach berry to character
		// And we are also holding grapple gun
		if(_SpawnedCharacterTool->ActorHasTag("GrappleGun"))
		{
			_SpawnedGrappleGun = Cast<ACharacterTool_GrappleGun>(_SpawnedCharacterTool);
			if(_SpawnedGrappleGun != nullptr && !_SpawnedGrappleGun->_HasBerry)
			{
				IBerryAquireable::Execute_PickupBerry(OtherActor);
				_SpawnedGrappleGun->AttachBerry();
			}
		}
	}
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

void APlayerCharacter::ToggleInventory_Implementation(const FInputActionValue& Instance)
{
	//Executing Blueprint Functionality
	InventoryBPAction();
}

void APlayerCharacter::ToggleJournal_Implementation(const FInputActionValue& Instance)
{
	HideHelpPanel();
	if (UIJournalInstance->GetVisibility() == ESlateVisibility::Visible)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
		if (PC)
		{
			PC->bShowMouseCursor = false;

			//set input mode to UI
			FInputModeGameOnly InputMode;
				

			PC->SetInputMode(InputMode);
		}
			
		UIJournalInstance->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
		if (PC)
		{
			PC->bShowMouseCursor = true;

			//set input mode to UI
			FInputModeGameAndUI InputMode;
			InputMode.SetWidgetToFocus((UIJournalInstance->TakeWidget()));
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

			PC->SetInputMode(InputMode);
		}
			
		UIJournalInstance->SetVisibility(ESlateVisibility::Visible);
	}
}

void APlayerCharacter::Aim_Implementation(const FInputActionValue& Instance)
{
	if(UKismetSystemLibrary::DoesImplementInterface(_SpawnedCharacterTool, UHeldItemInteractable::StaticClass()) )
	{
		IHeldItemInteractable::Execute_ToggleCamera(_SpawnedCharacterTool, this);
		IFireable::Execute_Grapple_Aim(_SpawnedCharacterTool, this);
	}
}

void APlayerCharacter::AimReleased_Implementation(const FInputActionValue& Instance)
{
	if(UKismetSystemLibrary::DoesImplementInterface(_SpawnedCharacterTool, UHeldItemInteractable::StaticClass()) )
	{
		IHeldItemInteractable::Execute_ToggleCamera(_SpawnedCharacterTool, this);
		IFireable::Execute_Grapple_Aim_Released(_SpawnedCharacterTool, this);
	}
}

void APlayerCharacter::ReleaseAim()
{
	FVector CurrentLocation = FVector(0.0f, 0.0f, 0.0f);
	_CameraSpringArmComponent->TargetArmLength =_CameraArmLengthDef;
	_CameraSpringArmComponent->SetRelativeLocation(CurrentLocation);
}

void APlayerCharacter::ReleasePlayer()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	_IsScanning = false;
}

void APlayerCharacter::LoadoutSwitchLeft_Implementation(const FInputActionValue& Instance)
{
	if(_ActiveLoadoutIndex > 0)
	{
		_ActiveLoadoutIndex--;
	}
	else
	{
		_ActiveLoadoutIndex = 2;
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Red, FString::Printf(TEXT("Left - %d"), _ActiveLoadoutIndex));

	SetCurrentLoadout();
}

void APlayerCharacter::LoadoutSwitchRight_Implementation(const FInputActionValue& Instance)
{
	if(_ActiveLoadoutIndex < 2)
	{
		_ActiveLoadoutIndex++;
	}
	else
	{
		_ActiveLoadoutIndex = 0;
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Red, FString::Printf(TEXT("Right - %d"), _ActiveLoadoutIndex));

	SetCurrentLoadout();
}

void APlayerCharacter::SetCurrentLoadout()
{
	if(UKismetSystemLibrary::DoesImplementInterface(_SpawnedCharacterTool, UBerryRemovable::StaticClass()))
	{
		IBerryRemovable::Execute_RemoveBerry(_SpawnedCharacterTool);
	}
	_SpawnedCharacterTool->Destroy();

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = this;
	
	switch(_ActiveLoadoutIndex)
	{
		case 0:
			{
				AActor* grapple = GetWorld()->SpawnActor(_GrappleGun, &_GrappleAttachPoint->GetComponentTransform(), spawnParams);
				grapple->AttachToComponent(_GrappleAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
			
				_SpawnedCharacterTool = Cast<ACharacterTool_Base>(grapple);
				_SpawnedCharacterTool->OnGrappleStart.AddDynamic(this, &APlayerCharacter::GrappleStart);
				_SpawnedCharacterTool->OnGrappleDuring.AddDynamic(this, &APlayerCharacter::GrappleDuring);
				_SpawnedCharacterTool->OnGrappleEnd.AddDynamic(this, &APlayerCharacter::GrappleEnd);
				_SpawnedCharacterTool->OnGrappleBerry.AddDynamic(this, &APlayerCharacter::ReleaseAim);
			}
			break;
		case 1:
			{
				AActor* camera = GetWorld()->SpawnActor(_Camera, &_GrappleAttachPoint->GetComponentTransform(), spawnParams);
				camera->AttachToComponent(_GrappleAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
				
				_SpawnedCharacterTool = Cast<ACharacterTool_Base>(camera);
				_SpawnedCharacterTool->OnSuccessfulAnimalPhotoTaken.AddDynamic(this, &APlayerCharacter::UpdateUI);
			}
			break;
		case 2:
			{
				AActor* scanner = GetWorld()->SpawnActor(_Scanner, &_GrappleAttachPoint->GetComponentTransform(), spawnParams);
				scanner->AttachToComponent(_GrappleAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
					
				_SpawnedCharacterTool = Cast<ACharacterTool_Base>(scanner);
				_SpawnedCharacterTool->OnReleasePlayer.AddDynamic(this, &APlayerCharacter::ReleasePlayer);
			}
			break;
		default:
			break;
	}
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

void APlayerCharacter::UpdateUI(FString animalType, ACreature_Base* animal, UUserWidget* screenshotInstance)
{
	if (ScreenshotWidgetInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Screenshot widget exists"));
		UDispalyScreenshots* TestUI = Cast<UDispalyScreenshots>(screenshotInstance);
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
		GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Red, FString::Printf(TEXT("Works")));
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
					Journal->SetImage(Journal->Deer, Journal->DeerSticker, ScreenshotTexture);
				}
				if (animalType == TEXT("Beetle"))
				{
					Journal->SetImage(Journal->Beetle, Journal->BeetleSticker, ScreenshotTexture);
				}
				if (animalType == TEXT("Lizard"))
				{
					Journal->SetImage(Journal->Lizard, Journal->LizardSticker, ScreenshotTexture);
				}
				if (animalType == TEXT("Snail"))
				{
					Journal->SetImage(Journal->Snail, Journal->SnailSticker, ScreenshotTexture);
				}
				if (animalType == TEXT("BerryBird"))
				{
					Journal->SetImage(Journal->BerryBird, Journal->BerryBirdSticker, ScreenshotTexture);
				}
				if (animalType == TEXT("GroundCreature"))
				{
					Journal->SetImage(Journal->GroundCreature, Journal->GroundCreatureSticker, ScreenshotTexture);
				}
				if (animalType == TEXT("LargeCreature"))
				{
					Journal->SetImage(Journal->LargeCreature, Journal->LargeCreatureSticker, ScreenshotTexture);
				}
				if (animalType == TEXT("RockCreature"))
				{
					Journal->SetImage(Journal->RockCreature, Journal->RockCreatureSticker, ScreenshotTexture);
				}
			}
		}
	}

	screenshotNum++;
}

void APlayerCharacter::PrimaryInteract_Implementation(const FInputActionValue& Instance)
{
	if(UKismetSystemLibrary::DoesImplementInterface(_SpawnedCharacterTool, UHeldItemInteractable::StaticClass()) )
	{
		IHeldItemInteractable::Execute_TakePhoto(_SpawnedCharacterTool, this, UIJournalInstance);
		IHeldItemInteractable::Execute_Scan(_SpawnedCharacterTool, this);
	}
	
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
	if(UKismetSystemLibrary::DoesImplementInterface(_SpawnedCharacterTool, UFireable::StaticClass()) )
	{
		bool hasFired = IFireable::Execute_Fire(_SpawnedCharacterTool, _ThirdPersonCameraComponent->GetForwardVector());
	}
}

void APlayerCharacter::CompletedPrimaryInteract_Implementation(const FInputActionValue& Instance)
{
	IInputActionable::CompletedPrimaryInteract_Implementation(Instance);
	
	if(UKismetSystemLibrary::DoesImplementInterface(_SpawnedCharacterTool, UFireable::StaticClass()) )
	{
		_HasFired = false;
		IFireable::Execute_Fire_Stop(_SpawnedCharacterTool);
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

}

void APlayerCharacter::GrappleStart()
{
	GetCharacterMovement()->MaxWalkSpeed = 0.0f;
	//GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	FVector CurrentLocation = FVector(0.0f, 0.0f, 0.0f);
	_CameraSpringArmComponent->TargetArmLength =_CameraArmLengthDef;
	_CameraSpringArmComponent->SetRelativeLocation(CurrentLocation);
}

void APlayerCharacter::GrappleDuring(FVector GrabPoint,  float grabForce)
{
	FVector distance = GrabPoint - this->GetActorLocation();

	//Limit to how short the cable can get
	if(abs(distance.Z) > _MinGrappleCableLength)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

		//Cap to velocity so the little guy doesn't ping around like a tennis ball
		if(abs(GetCharacterMovement()->Velocity.X) < _MaxGrappleVelocity &&
		   abs(GetCharacterMovement()->Velocity.Y) < 950.f)
		{
			GetCharacterMovement()->AddForce(FVector(
				(GrabPoint.X - GetActorLocation().X) * (grabForce * 1.5f),
				(GrabPoint.Y - GetActorLocation().Y) * (grabForce * 1.5f),
				(GrabPoint.Z - GetActorLocation().Z) * (grabForce / 2.5f)
				));
		}
	}
	//If too close to fly trap 
	else
	{
		if (!GetCharacterMovement()->IsFalling())
		{
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
		}
	}
}

void APlayerCharacter::GrappleEnd()
{
	ReleasePlayer();
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

