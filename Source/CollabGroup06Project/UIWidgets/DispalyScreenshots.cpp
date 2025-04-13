// Fill out your copyright notice in the Description page of Project Settings.


#include "DispalyScreenshots.h"

#include "Components/Image.h"


void UDispalyScreenshots::SetImage(UTexture2D* NewTexture)
{
	if (Screenshot && NewTexture)
	{
		Screenshot->SetBrushFromTexture(NewTexture);
		PlayAnimation(ShutterAnim, 0.0f, 1);
	}
}

void UDispalyScreenshots::NativeConstruct()
{
	Super::NativeConstruct();
}
