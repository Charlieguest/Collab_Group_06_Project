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
	UPROPERTY(meta = (BindWidget))
	UImage* LargeCreature;
	UPROPERTY(meta = (BindWidget))
	UImage* Snail;
	UPROPERTY(meta = (BindWidget))
	UImage* RockCreature;
	UPROPERTY(meta = (BindWidget))
	UImage* Beetle;
	UPROPERTY(meta = (BindWidget))
	UImage* GroundCreature;
	UPROPERTY(meta = (BindWidget))
	UImage* BerryBird;
	UPROPERTY(meta = (BindWidget))
	UImage* Lizard;

	UFUNCTION()
	void SetImage(UImage* animalImage, UTexture2D* NewTexture);

	virtual void NativeConstruct() override;
};
