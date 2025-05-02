#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "CollabGroup06Project/Interfaces/InputActionable.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "CollabGroup06Project/Interfaces/BerryAquireable.h"
#include "PlayerCharacter.generated.h"


class ACharacterTool_Camera;
class ACharacterTool_Base;
class ACharacterTool_GrappleGun;
class ACharacterTool_Scanner;
class ACreature_Base;
class APlayerBerry;
class USphereComponent;
class USpringArmComponent;
class UCameraComponent;
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

	/* ------------------------------- */
	/* ------------------------------- */
	/* ---- Camera mode functions ---- */
	/* ------------------------------- */
	/* ------------------------------- */

	virtual void ToggleJournal_Implementation(const FInputActionValue& Instance) override;

	UFUNCTION(BlueprintCallable, Category = "Screenshot")
	UTexture2D* LoadScreenshotAsTexture();

	UFUNCTION(BlueprintCallable, Category = "Screenshot")
	void UpdateUI(FString animalType, ACreature_Base* creatureBase, UUserWidget* screenshotInstance);

	/* ------------------------------- */
	/* ------------------------------- */
	/* ---- Grapple Functions -------- */
	/* ------------------------------- */
	/* ------------------------------- */

	virtual void PrimaryInteract_Implementation(const FInputActionValue& Instance) override;
	virtual void CompletedPrimaryInteract_Implementation(const FInputActionValue& Instance) override;
	virtual void Interact_Implementation(const FInputActionValue& Instance) override;
	virtual void Aim_Implementation(const FInputActionValue& Instance) override;
	virtual void AimReleased_Implementation(const FInputActionValue& Instance) override;

	virtual void Sprint_Implementation(const FInputActionValue& Instance) override;
	virtual void SprintComplete_Implementation(const FInputActionValue& Instance) override;

	UFUNCTION(BlueprintNativeEvent)
	void SprintStart();
	UFUNCTION(BlueprintNativeEvent)
	void SprintEnd();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSpeed)
	float _SprintSpeed = 850.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSpeed)
	float _WalkSpeed = 600.0f;
	
	UFUNCTION()
	void ReleaseAim();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CAMERA_ZOOM_DAMPEN)
	bool _IsAiming;
	
	UFUNCTION()
	void Pickup_Berry();
	
	void GrappleShoot();
	FTimerHandle _GrappleShootDelay;
	bool _HasFired;
	
	UFUNCTION()
	void GrappleStart();
	UFUNCTION()
	void GrappleDuring(FVector grabPoint, float grabForce);
	UFUNCTION()
	void GrappleEnd();

	UFUNCTION(BlueprintNativeEvent)
	void ActivateAnimal();

	//Components

	FRotator MovementRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CAMERA_ZOOM_DAMPEN)
	UCameraComponent* _ThirdPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CAMERA_ZOOM_DAMPEN)
	USpringArmComponent* _CameraSpringArmComponent;

	TObjectPtr<USphereComponent> _InteractionZoneSphereComponent;

	FVector _InteractZoneOffset = FVector(450.0f, 0.0f, -10.0f);

	/* --------------------------------------- */
	/* ---- Inventory Blueprint Functions ---- */
	/* --------------------------------------- */

	UFUNCTION(BlueprintNativeEvent)
	void PickUpInventoryItem(AActor* interactItem);

	UFUNCTION(BlueprintNativeEvent)
	void InventoryBPAction();

	UFUNCTION(BlueprintNativeEvent, CallInEditor)
	void SearchInventory(const FString& requiredItem, bool isInteracting);

	UFUNCTION(BlueprintNativeEvent)
	void HideHelpPanel();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _RequiredItemFound;
	
	/* ------------------------------- */
	/* ------ Scan Functions --------- */
	/* ------------------------------- */

	UFUNCTION()
	void ReleasePlayer();

	/* ------------------------------- */
	/* ----- Camera Components ------- */
	/* ------------------------------- */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementVars)
	float _CameraArmLengthDef = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementVars)
	float _CameraArmLengthCam = -100.0f;

	UPROPERTY(BlueprintReadWrite, Category=Speeds);
	bool bIsSprinting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraSystem)
	bool bIsCameraOpen = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MovementVars)
	bool bToggleInput = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraSystem)
	FVector PreviousLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraSystem)
	FString ScannedAnimal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraSystem)
	float _ScanDistance = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraSystem)
	float _PhotographDistance = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACharacterTool_Camera> _Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<ACharacterTool_Base> _SpawnedCharacterTool;

	//Camera border UI
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> ScreenshotClass;
	UUserWidget* ScreenshotWidgetInstance;

	//Journal UI
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> UIJournalClass;
	UUserWidget* UIJournalInstance;

	//Screenshot file number
	int screenshotNum;
	
	FTimerHandle _UpdateUIDelayTimer;
	FTimerDelegate _UpdateUIDelayDelegate;

	UFUNCTION()
	void SetHoldingCamera(bool isHoldingCamera);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraSystem)
	bool _IsHoldingCamera;

	/* ------------------------------- */
	/* ------ Grapple Components ----- */
	/* ------------------------------- */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "True"))
	TObjectPtr<UArrowComponent> _GrappleAttachPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ACharacterTool_GrappleGun> _GrappleGun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<ACharacterTool_GrappleGun> _SpawnedGrappleGun;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float _MinGrappleCableLength;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float _MaxGrappleVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool _IsGrappling;
	
	/* ------------------------------- */
	/* ------ Scan Components -------- */
	/* ------------------------------- */

	FTimerHandle _PerformScanTimerHandle;
	bool _IsScanning;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ACharacterTool_Scanner> _Scanner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> _Animal;

	/* ------------------------------- */
	/* ------ Loadout Switching ------ */
	/* ------------------------------- */

	int _ActiveLoadoutIndex = 0;

	void LoadoutSwitchLeft_Implementation(const FInputActionValue& Instance) override;
	void LoadoutSwitchRight_Implementation(const FInputActionValue& Instance) override;

	void SetCurrentLoadout();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintNativeEvent)
	void UpdateLoadout(int previousIndex);

};
