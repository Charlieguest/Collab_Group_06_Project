// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameRule.h"
#include "GameRule_PhotographAnimals.generated.h"


class ACreature_Base;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COLLABGROUP06PROJECT_API UGameRule_PhotographAnimals : public UGameRule
{
	GENERATED_BODY()

public:
	UGameRule_PhotographAnimals();

	virtual void Init() override;
	
protected:
	virtual void BeginPlay() override;

	int _CreaturesRemaining;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<ACreature_Base>> _Creatures;

	UFUNCTION()
	void Handle_Photographed(class ACreature_Base* animal, AController* causer);
};
