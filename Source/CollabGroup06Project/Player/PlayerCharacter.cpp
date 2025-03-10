#include "PlayerCharacter.h"

#include "InputActionValue.h"
#include "Components/ArrowComponent.h"
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

	_GrappleAttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("GappleAttachPoint"));
	_GrappleAttachPoint->SetupAttachment(GetRootComponent());
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	
	
}

void APlayerCharacter::Move_Implementation(const FInputActionValue& Instance)
{
	if(Controller != nullptr)
	{
		const FVector2d MoveValue = Instance.Get<FVector2d>();
		const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

		if(MoveValue.Y != 0.0f)
		{
			const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);
			AddMovementInput(Direction, MoveValue.Y);
		}

		if(MoveValue.X != 0.0f)
		{
			const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);
			AddMovementInput(Direction, MoveValue.X);
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
	Super::Jump();
}

void APlayerCharacter::PrimaryInteract_Implementation(const FInputActionValue& Instance)
{
	IInputActionable::PrimaryInteract_Implementation(Instance);
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Emerald, FString::Printf(TEXT("Ched")));
}

void APlayerCharacter::Init_Implementation()
{
}