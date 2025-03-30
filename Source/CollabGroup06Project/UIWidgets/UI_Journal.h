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
	UPROPERTY(meta = (BindWidget))
	UImage* Deer;
	UImage* LargeCreature;
	UImage* Snail;
	UImage* RockCreature;
	UImage* Beetle;
	UImage* GroundCreature;
	UImage* BerryBird;
	UImage* Lizard;

	UFUNCTION()
	void SetImage(UImage* animalImage, UTexture2D* NewTexture);

	virtual void NativeConstruct() override;
};
