// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "DispalyScreenshots.generated.h"

/**
 * 
 */
UCLASS()
class COLLABGROUP06PROJECT_API UDispalyScreenshots : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UImage* Screenshot;

	UFUNCTION()
	void SetImage(UTexture2D* NewTexture);

protected:
	virtual void NativeConstruct() override;
};
