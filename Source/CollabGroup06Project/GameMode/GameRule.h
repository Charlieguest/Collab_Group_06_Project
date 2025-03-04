#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameRule.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameRuleCompleteSignature, class UGameRule*, rule);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COLLABGROUP06PROJECT_API UGameRule : public UActorComponent
{
	GENERATED_BODY()

public:
	UGameRule();
	FGameRuleCompleteSignature OnGameRuleComplete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _IsOptional;
	
	void BroadcastGameRuleComplete();

	UFUNCTION()
	void Init();
};
