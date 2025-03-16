#include "PlayerCharacter.h"

#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "CollabGroup06Project/Player/PlayerTools/GrappleGun.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "CollabGroup06Project/UIWidgets/DispalyScreenshots.h"

APlayerCharacter::APlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);

	_CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	_CameraSpringArmComponent->SetupAttachment(RootComponent);
	_CameraSpringArmComponent->bUsePawnControlRotation = true;
	
	_ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
	_ThirdPersonCameraComponent->SetupAttachment(_CameraSpringArmComponent);

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
		if (ScreenshotWidgetInstance)
		{
			ScreenshotWidgetInstance->AddToViewport();
			ScreenshotWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = this;

	_SpawnedGrappleGun = GetWorld()->SpawnActor(_GrappleGun, &_GrappleAttachPoint->GetComponentTransform(), spawnParams);
	_SpawnedGrappleGun->AttachToComponent(_GrappleAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);

	AGrappleGun* grappleGun = Cast<AGrappleGun>(_SpawnedGrappleGun);
	grappleGun->OnGrappleStart.AddDynamic(this, &APlayerCharacter::GrappleStart);
	grappleGun->OnGrappleDuring.AddDynamic(this, &APlayerCharacter::GrappleDuring);
	grappleGun->OnGrappleEnd.AddDynamic(this, &APlayerCharacter::GrappleEnd);
	
}


void APlayerCharacter::Move_Implementation(const FInputActionValue& Instance)
{
	if (!bToggleInput)
	{	
		if(Controller != nullptr)
		{
			const FVector2d MoveValue = Instance.Get<FVector2d>();
			const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

			if(MoveValue.Y != 0.0f)
			{
				if (bIsCameraOpen)
				{
					float Min = -200.0f;
					float Max = 200.0f;
					
					FVector NewLocation = _CameraSpringArmComponent->GetRelativeLocation();
					NewLocation.Y += MoveValue.Y * 10.0f;
					NewLocation.Y = FMath::Clamp(NewLocation.Y, Min, Max);
					_CameraSpringArmComponent->SetRelativeLocation(NewLocation);
					
				}
				else
				{
					const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);
					AddMovementInput(Direction, MoveValue.Y);
					GetCapsuleComponent()->SetWorldRotation(MovementRotation);
				}
				
			}

			if(MoveValue.X != 0.0f)
			{
				if (bIsCameraOpen)
				{
					float Min = -200.0f;
					float Max = 200.0f;
					
					FVector NewLocation = _CameraSpringArmComponent->GetRelativeLocation();
					NewLocation.X += MoveValue.X * 10.0f;
					NewLocation.X = FMath::Clamp(NewLocation.X, Min, Max);
					_CameraSpringArmComponent->SetRelativeLocation(NewLocation);
					
				}
				
				else
				{
					const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);
					AddMovementInput(Direction, MoveValue.X);
					GetCapsuleComponent()->SetWorldRotation(MovementRotation);
				}
			}
		}
	}
	
}

void APlayerCharacter::Look_Implementation(const FInputActionValue& Instance)
{
	if (bIsCameraOpen)
	{
		
		if(Controller != nullptr)
		{
			FRotator CurrentRotation = Controller->GetControlRotation();
			FRotator TargetRotation = FRotator(0.0f, CurrentRotation.Yaw, 0.0f);
			FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 5.0f);
			Controller->SetControlRotation(NewRotation);
		}
	}
	else
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

void APlayerCharacter::ToggleCamera_Implementation(const FInputActionValue& Instance)
{
	bIsCameraOpen = !bIsCameraOpen;
	if (bIsCameraOpen)
	{
		if (ScreenshotWidgetInstance)
		{
			ScreenshotWidgetInstance->SetVisibility(ESlateVisibility::Visible);
		}
		FVector CurrentLocation = _CameraSpringArmComponent->GetRelativeLocation();
		CurrentLocation.Z =+ 200.0f;
		
		_CameraSpringArmComponent->TargetArmLength = _CameraArmLengthCam;
		_CameraSpringArmComponent->SetRelativeLocation(CurrentLocation);
		
	}
	else
	{
		FVector CurrentLocation = FVector(0.0f, 0.0f, 0.0f);
		
		_CameraSpringArmComponent->TargetArmLength = _CameraArmLengthDef;
		_CameraSpringArmComponent->SetRelativeLocation(CurrentLocation);
		if (ScreenshotWidgetInstance)
		{
			ScreenshotWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void APlayerCharacter::TakePhoto_Implementation(const FInputActionValue& Instance)
{
	if(bIsCameraOpen)
	{
		CaptureScreenshot();
		UpdateUI();
	}
}

void APlayerCharacter::Scan_Implementation(const FInputActionValue& Instance)
{
	IInputActionable::Scan_Implementation(Instance);
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
	UE_LOG(LogTemp, Warning, TEXT("Importing text"));
	return UKismetRenderingLibrary::ImportFileAsTexture2D(this, ScreenshotPath);
}

void APlayerCharacter::UpdateUI()
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
}

void APlayerCharacter::PrimaryInteract_Implementation(const FInputActionValue& Instance)
{
	IInputActionable::PrimaryInteract_Implementation(Instance);

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
		IFireable::Execute_Fire_Stop(_SpawnedGrappleGun);
	}
}

void APlayerCharacter::GrappleStart()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
}

void APlayerCharacter::GrappleDuring(FVector GrabPoint)
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.2f, FColor::Green, FString::Printf(TEXT("Grab Point X: %f, Y: %f, Z: %f"), GrabPoint.X, GrabPoint.Y, GrabPoint.Z));
	GetCharacterMovement()->AddForce((GrabPoint - GetActorLocation()) * 700);
}

void APlayerCharacter::GrappleEnd()
{
	if (!GetCharacterMovement()->IsFalling())
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
	}
}

void APlayerCharacter::Init_Implementation()
{
}

