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
	//Journal images
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
	
	//Journal Stickers
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* DeerSticker;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* LargeCreatureSticker;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* SnailSticker;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* RockCreatureSticker;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* BeetleSticker;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* GroundCreatureSticker;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* BerryBirdSticker;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UImage* LizardSticker;

	UFUNCTION()
	void SetImage(UImage* animalImage, UImage* animalSticker, UTexture2D* NewTexture);

	virtual void NativeConstruct() override;
};
