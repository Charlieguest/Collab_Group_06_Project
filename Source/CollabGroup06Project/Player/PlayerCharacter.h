#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "CollabGroup06Project/Interfaces/InputActionable.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "CollabGroup06Project/Interfaces/Interact.h"
#include "PlayerCharacter.generated.h"


class USphereComponent;
class USpringArmComponent;
struct FInputActionValue;
class UCameraComponent;

UCLASS()
class COLLABGROUP06PROJECT_API APlayerCharacter : public ACharacter, public IInputActionable, public IInteract
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

	virtual void Interact_Implementation(const FInputActionValue& Instance) override;

	//Camera mode functions

	virtual void ToggleCamera_Implementation(const FInputActionValue& Instance) override;
	
	virtual void TakePhoto_Implementation(const FInputActionValue& Instance) override;

	virtual void Scan_Implementation(const FInputActionValue& Instance) override;
	
	
	UFUNCTION(BlueprintCallable, Category = "Screenshot")
	void CaptureScreenshot();

	UFUNCTION(BlueprintCallable, Category = "Screenshot")
	UTexture2D* LoadScreenshotAsTexture();

	UFUNCTION(BlueprintCallable, Category = "Screenshot")
	void UpdateUI();
	
	

	//Components

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CAMERA_ZOOM_DAMPEN)
	UCameraComponent* _ThirdPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CAMERA_ZOOM_DAMPEN)
	USpringArmComponent* _CameraSpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CAMERA_ZOOM_DAMPEN)
	USphereComponent* _InteractionZoneSphereComponent;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CamerSystem)
	bool bIsCameraOpen = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementVars)
	bool bToggleInput = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
	FVector interactZoneOffset = {450.0,0.0,-30.0};

	//Testing UI for screenshotting
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> ScreenshotClass;
	UUserWidget* ScreenshotWidgetInstance;
};
