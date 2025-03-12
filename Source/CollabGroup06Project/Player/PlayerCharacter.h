#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "CollabGroup06Project/Interfaces/InputActionable.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
struct FInputActionValue;
class UCameraComponent;

UCLASS()
class COLLABGROUP06PROJECT_API APlayerCharacter : public ACharacter, public IInputActionable
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	
	virtual void BeginPlay() override;

	/** Character Initialisation */
	UFUNCTION(BlueprintNativeEvent)
	void Init();

	virtual void Move_Implementation(const FInputActionValue& Instance) override;

	virtual void Look_Implementation(const FInputActionValue& Instance) override;

	virtual void Jump_Implementation(const FInputActionValue& Instance) override;

	virtual void ToggleCamera_Implementation(const FInputActionValue& Instance) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CAMERA_ZOOM_DAMPEN)
	UCameraComponent* _ThirdPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CAMERA_ZOOM_DAMPEN)
	USpringArmComponent* _CameraSpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementVars)
	float _WalkSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementVars)
	float _SprintSpeed = 700.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementVars)
	float _CameraArmLengthDef = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementVars)
	float _CameraArmLengthCam = -100.0f;

	UPROPERTY(BlueprintReadWrite, Category=Speeds);
	bool bIsSprinting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementVars)
	bool bIsCameraOpen = false;
};
