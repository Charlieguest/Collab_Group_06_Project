#include "PlayerCharController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerCharacter.h"
#include "CollabGroup06Project/DataAssets/InputAssets.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

APlayerCharController::APlayerCharController()
{
}

void APlayerCharController::BeginPlay()
{
	Super::BeginPlay();

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if(_InputMappingContext)
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(_InputMappingContext, 0);
		}
	}
}

void APlayerCharController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* PEI = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		if(_InputActions.LoadSynchronous())
		{
			PEI->BindAction(_InputActions->Jump.LoadSynchronous(), ETriggerEvent::Triggered, this, &APlayerCharController::CAM_Jump);
			PEI->BindAction(_InputActions->Move.LoadSynchronous(), ETriggerEvent::Triggered, this, &APlayerCharController::CAM_Move);
			PEI->BindAction(_InputActions->Look.LoadSynchronous(), ETriggerEvent::Triggered, this, &APlayerCharController::CAM_Look);
			PEI->BindAction(_InputActions->ToggleJournal.LoadSynchronous(), ETriggerEvent::Started, this, &APlayerCharController::CAM_JournalToggle);
			PEI->BindAction(_InputActions->ToggleInventory.LoadSynchronous(), ETriggerEvent::Started, this, &APlayerCharController::CAM_InventoryToggle);
			PEI->BindAction(_InputActions->PrimaryInteract.LoadSynchronous(), ETriggerEvent::Triggered, this, &APlayerCharController::CAM_PrimaryInteract);
			PEI->BindAction(_InputActions->PrimaryInteract.LoadSynchronous(), ETriggerEvent::Completed, this, &APlayerCharController::CAM_CompletePrimaryInteract);
			PEI->BindAction(_InputActions->ItemInteract.LoadSynchronous(), ETriggerEvent::Triggered, this, &APlayerCharController::CAM_ItemInteract);
			PEI->BindAction(_InputActions->Aim.LoadSynchronous(), ETriggerEvent::Started, this, &APlayerCharController::CAM_Aim);
			PEI->BindAction(_InputActions->Aim.LoadSynchronous(), ETriggerEvent::Completed, this, &APlayerCharController::CAM_AimFinished);
			PEI->BindAction(_InputActions->LoadoutSwitchLeft.LoadSynchronous(), ETriggerEvent::Started, this, &APlayerCharController::CAM_LoadoutSwitchLeft);
			PEI->BindAction(_InputActions->LoadoutSwitchRight.LoadSynchronous(), ETriggerEvent::Started, this, &APlayerCharController::CAM_LoadoutSwitchRight);
		}
	}
}

void APlayerCharController::Init_Implementation()
{
}

void APlayerCharController::Handle_MatchStarted_Implementation()
{
	UWorld* const world = GetWorld();
	GEngine->AddOnScreenDebugMessage(-1, 5.f,FColor::Black, FString::Printf(TEXT("Player Created")));

	AActor* tempStart = UGameplayStatics::GetGameMode(world)->FindPlayerStart(this);
	FVector spawnLocation = _PlayerSpawnLoc;
	FRotator spawnRotation = FRotator(0.0f, _PlayerSpawnRotY, 0.0f);

	FActorSpawnParameters SpawnParameters;
	_PlayerPawn = world->SpawnActor<APawn>(_PawnToSpawn, spawnLocation, spawnRotation, SpawnParameters);
	Possess(_PlayerPawn);
	
	if(APlayerCharacter* castedPawn = Cast<APlayerCharacter>(_PlayerPawn))
	{
		//TODO: Bind to any relevant events
		castedPawn->Init();
		
		this->SetViewTarget(castedPawn);
		//castedPawn->SetActorLocation(FVector(0.0f, 0.0f, 10.0f));
	}
	
	IMatchStateHandler::Handle_MatchStarted_Implementation();
}

void APlayerCharController::Handle_MatchEnded_Implementation()
{
	IMatchStateHandler::Handle_MatchEnded_Implementation();
}

void APlayerCharController::CAM_Jump(const FInputActionValue& Instance)
{
	if(UKismetSystemLibrary::DoesImplementInterface(_PlayerPawn, UInputActionable::StaticClass()))
	{
		IInputActionable::Execute_Jump(_PlayerPawn, Instance);
	}
}

void APlayerCharController::CAM_Move(const FInputActionValue& Instance)
{
	if(UKismetSystemLibrary::DoesImplementInterface(_PlayerPawn, UInputActionable::StaticClass()))
	{
		IInputActionable::Execute_Move(_PlayerPawn, Instance);
	}
}

void APlayerCharController::CAM_Look(const FInputActionValue& Instance)
{
	if(UKismetSystemLibrary::DoesImplementInterface(_PlayerPawn, UInputActionable::StaticClass()))
	{
		IInputActionable::Execute_Look(_PlayerPawn, Instance);
	}
}

void APlayerCharController::CAM_InventoryToggle(const FInputActionValue& Instance)
{
	if(UKismetSystemLibrary::DoesImplementInterface(_PlayerPawn, UInputActionable::StaticClass()))
	{
		IInputActionable::Execute_ToggleInventory(_PlayerPawn, Instance);
	}
}

void APlayerCharController::CAM_JournalToggle(const FInputActionValue& Instance)
{
	if(UKismetSystemLibrary::DoesImplementInterface(_PlayerPawn, UInputActionable::StaticClass()))
	{
		IInputActionable::Execute_ToggleJournal(_PlayerPawn, Instance);
	}
}

void APlayerCharController::CAM_PrimaryInteract(const FInputActionValue& Instance)
{
	if(UKismetSystemLibrary::DoesImplementInterface(_PlayerPawn, UInputActionable::StaticClass()))
	{
		IInputActionable::Execute_PrimaryInteract(_PlayerPawn, Instance);
	}
}

void APlayerCharController::CAM_CompletePrimaryInteract(const FInputActionValue& Instance)
{
	if(UKismetSystemLibrary::DoesImplementInterface(_PlayerPawn, UInputActionable::StaticClass()))
	{
		IInputActionable::Execute_CompletedPrimaryInteract(_PlayerPawn, Instance);
	}
}

void APlayerCharController::CAM_ItemInteract(const FInputActionValue& Instance)
{
	if(UKismetSystemLibrary::DoesImplementInterface(_PlayerPawn, UInputActionable::StaticClass()))
	{
		IInputActionable::Execute_Interact(_PlayerPawn, Instance);
	}
}

void APlayerCharController::CAM_Aim(const FInputActionValue& Instance)
{
	if(UKismetSystemLibrary::DoesImplementInterface(_PlayerPawn, UInputActionable::StaticClass()))
	{
		IInputActionable::Execute_Aim(_PlayerPawn, Instance);
	}
}

void APlayerCharController::CAM_AimFinished(const FInputActionValue& Instance)
{
	if(UKismetSystemLibrary::DoesImplementInterface(_PlayerPawn, UInputActionable::StaticClass()))
	{
		IInputActionable::Execute_AimReleased(_PlayerPawn, Instance);
	}
}

void APlayerCharController::CAM_LoadoutSwitchLeft(const FInputActionValue& Instance)
{
	if(UKismetSystemLibrary::DoesImplementInterface(_PlayerPawn, UInputActionable::StaticClass()))
	{
		IInputActionable::Execute_LoadoutSwitchLeft(_PlayerPawn, Instance);
	}
}

void APlayerCharController::CAM_LoadoutSwitchRight(const FInputActionValue& Instance)
{
	if(UKismetSystemLibrary::DoesImplementInterface(_PlayerPawn, UInputActionable::StaticClass()))
	{
		IInputActionable::Execute_LoadoutSwitchRight(_PlayerPawn, Instance);
	}
}
