#pragma once

#include "CoreMinimal.h"
#include "CharacterTool_Base.h"
#include "GameFramework/Actor.h"
#include "CharacterTool_Camera.generated.h"

class ACreature_Base;

UCLASS()
class COLLABGROUP06PROJECT_API ACharacterTool_Camera : public ACharacterTool_Base
{
	GENERATED_BODY()

public:
	ACharacterTool_Camera();

	virtual void TakePhoto_Implementation(APlayerCharacter* player,  UUserWidget* journal) override;

	virtual void ToggleCamera_Implementation(APlayerCharacter* player) override;

	UFUNCTION(BlueprintCallable, Category = "Screenshot")
	void CaptureScreenshot();
	
	UFUNCTION(BlueprintCallable, Category = "Screenshot")
	bool IsAnythingInCameraView(UWorld* world, APlayerCharacter* player);
	
	UUserWidget* ScreenshotWidgetInstance;

	UFUNCTION(BlueprintCallable, Category = "Screenshot")
	void UpdateUIOnPlayer(FString animalType, ACreature_Base* animal);
	
	FTimerHandle _UpdateUIDelayTimer;
	FTimerDelegate _UpdateUIDelayDelegate;
	
protected:

	bool _CameraOpen;
	
	//Camera border UI
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> ScreenshotClass;
	
	virtual void BeginPlay() override;
};
