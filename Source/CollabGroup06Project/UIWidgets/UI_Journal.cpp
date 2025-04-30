// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Journal.h"

#include "Components/Image.h"

void UUI_Journal::SetImage(UImage* animalImage, UImage* animalSticker, UTexture2D* NewTexture)
{
	if (animalImage && NewTexture)
	{
		animalImage->SetBrushFromTexture(NewTexture);
		animalSticker->SetVisibility(ESlateVisibility::Visible);
	}
}

void UUI_Journal::NativeConstruct()
{
	Super::NativeConstruct();
}
