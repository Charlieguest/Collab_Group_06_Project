#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "CollabGroup06Project/Interfaces/InputActionable.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AGrappleGun;
struct FInputActionValue;


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

	virtual void PrimaryInteract_Implementation(const FInputActionValue& Instance) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CAMERA_ZOOM_DAMPEN)
	UCameraComponent* _ThirdPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CAMERA_ZOOM_DAMPEN)
	USpringArmComponent* _CameraSpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementVars)
	float _WalkSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementVars)
	float _SprintSpeed = 700.0f;

	UPROPERTY(BlueprintReadWrite, Category=Speeds);
	bool bIsSprinting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> _GrappleAttachPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AGrappleGun> _GrappleGun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> _SpawnedGrabbleGun;
};
