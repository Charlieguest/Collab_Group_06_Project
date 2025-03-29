#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "CollabGroup06Project/Interfaces/InputActionable.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCharacter.generated.h"


class APlayerBerry;
class USphereComponent;
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

	virtual void ToggleInventory_Implementation(const FInputActionValue& Intance) override;

	/* ------------------------------- */
	/* ------------------------------- */
	/* ---- Camera mode functions ---- */
	/* ------------------------------- */
	/* ------------------------------- */

	virtual void ToggleCamera_Implementation(const FInputActionValue& Instance) override;
	
	virtual void TakePhoto_Implementation(const FInputActionValue& Instance) override;

	virtual void Scan_Implementation(const FInputActionValue& Instance) override;
	
	UFUNCTION(BlueprintCallable, Category = "Screenshot")
	void CaptureScreenshot();

	UFUNCTION(BlueprintCallable, Category = "Screenshot")
	UTexture2D* LoadScreenshotAsTexture();

	UFUNCTION(BlueprintCallable, Category = "Screenshot")
	void UpdateUI();

	UFUNCTION(BlueprintCallable, Category = "Screenshot")
	bool isAnythingInCameraView(UWorld* world);

	/* ------------------------------- */
	/* ------------------------------- */
	/* ---- Grapple Functions -------- */
	/* ------------------------------- */
	/* ------------------------------- */

	virtual void PrimaryInteract_Implementation(const FInputActionValue& Instance) override;
	virtual void CompletedPrimaryInteract_Implementation(const FInputActionValue& Instance) override;
	virtual void Interact_Implementation(const FInputActionValue& Instance) override;

	UFUNCTION()
	void Pickup_Berry();
	
	void GrappleShoot();
	FTimerHandle _GrappleShootDelay;
	bool _HasFired;

	
	UFUNCTION()
	void GrappleStart();
	UFUNCTION()
	void GrappleDuring(FVector grabPoint);
	UFUNCTION()
	void GrappleEnd();

	UFUNCTION(BlueprintNativeEvent)
	void ActivateAnimal();

	UFUNCTION(BlueprintNativeEvent)
	void PickUpInventoryItem(AActor* interactItem);

	UFUNCTION(BlueprintNativeEvent)
	void InventoryBPAction();
	
	/* ------------------------------- */
	/* ------ Scan Functions --------- */
	/* ------------------------------- */

	void ReleasePlayer();
	
	//Components

	FRotator MovementRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CAMERA_ZOOM_DAMPEN)
	UCameraComponent* _ThirdPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CAMERA_ZOOM_DAMPEN)
	USpringArmComponent* _CameraSpringArmComponent;

	TObjectPtr<USphereComponent> _InteractionZoneSphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementVars)
	float _WalkSpeed = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementVars)
	float _SprintSpeed = 700.0f;

	FVector _InteractZoneOffset = FVector(450.0f, 0.0f, -10.0f);

	/* ------------------------------- */
	/* ----- Camera Components ------- */
	/* ------------------------------- */
	
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

	//Testing UI for screenshotting
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> ScreenshotClass;
	UUserWidget* ScreenshotWidgetInstance;

	/* ------------------------------- */
	/* ---- Grapple Components ------- */
	/* ------------------------------- */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "True"))
	TObjectPtr<UArrowComponent> _GrappleAttachPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AGrappleGun> _GrappleGun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<AGrappleGun> _SpawnedGrappleGun;


	/* ------------------------------- */
	/* ------ Scan Components -------- */
	/* ------------------------------- */

	FTimerHandle _PerformScanTimerHandle;
	bool _IsScanning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> _Animal;
};
