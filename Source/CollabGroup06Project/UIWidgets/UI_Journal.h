// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_Journal.generated.h"

/**
 * 
 */
UCLASS()
class COLLABGROUP06PROJECT_API UUI_Journal : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* Deer;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* LargeCreature;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* Snail;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* RockCreature;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* Beetle;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* GroundCreature;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* BerryBird;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* Lizard;

	UFUNCTION()
	void SetImage(UImage* animalImage, UTexture2D* NewTexture);

	virtual void NativeConstruct() override;
};
