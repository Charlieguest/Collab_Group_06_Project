#include "PlayerCharacter.h"

#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerCharacter::APlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);

	_CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	_CameraSpringArmComponent->SetupAttachment(RootComponent);
	_CameraSpringArmComponent->bUsePawnControlRotation = true;
	
	_ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
	_ThirdPersonCameraComponent->SetupAttachment(_CameraSpringArmComponent);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
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
		
	}
}


void APlayerCharacter::Init_Implementation()
{
}

