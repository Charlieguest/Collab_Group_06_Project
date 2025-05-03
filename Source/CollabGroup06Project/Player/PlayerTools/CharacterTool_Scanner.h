#pragma once

#include "CoreMinimal.h"
#include "CharacterTool_Base.h"
#include "CharacterTool_Scanner.generated.h"

UCLASS()
class COLLABGROUP06PROJECT_API ACharacterTool_Scanner : public ACharacterTool_Base
{
	GENERATED_BODY()

public:
	ACharacterTool_Scanner();

	FTimerHandle _PerformScanTimerHandle;

	UPROPERTY(BlueprintReadOnly)
	bool _IsScanning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Scanner")
	float _ScanTime = 2.0f;

	virtual void Scan_Implementation(APlayerCharacter* player) override;
	
	UFUNCTION(BlueprintNativeEvent)
	void BeginScan();
	
	
	void ReleasePlayer();

protected:
	virtual void BeginPlay() override;
};
