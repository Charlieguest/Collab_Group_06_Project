#pragma once

#include "CoreMinimal.h"
#include "CollabGroup06Project/Interfaces/Fireable.h"
#include "CollabGroup06Project/Interfaces/PhotoTakeable.h"
#include "GameFramework/Actor.h"
#include "CharacterCamera.generated.h"

class ACreature_Base;

UCLASS()
class COLLABGROUP06PROJECT_API ACharacterCamera : public AActor, public IPhotoTakeable
{
	GENERATED_BODY()

public:
	ACharacterCamera();

	virtual void TakePhoto_Implementation(APlayerCharacter* player,  UUserWidget* journal) override;

	virtual void ToggleCamera_Implementation(APlayerCharacter* player) override;

	UFUNCTION(BlueprintCallable, Category = "Screenshot")
	void CaptureScreenshot();
	
	UFUNCTION(BlueprintCallable, Category = "Screenshot")
	bool IsAnythingInCameraView(UWorld* world, APlayerCharacter* player);
	
	UUserWidget* ScreenshotWidgetInstance;
	
protected:

	bool _CameraOpen;

	FTimerHandle _UpdateUIDelayTimer;
	FTimerDelegate _UpdateUIDelayDelegate;
	
	//Camera border UI
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> ScreenshotClass;
	
	virtual void BeginPlay() override;
};
