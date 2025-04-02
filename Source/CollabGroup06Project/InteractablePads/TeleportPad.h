#pragma once

#include "InteractPad_Base.h"
#include "GameFramework/Character.h"
#include "TeleportPad.generated.h"

UCLASS()
class COLLABGROUP06PROJECT_API ATeleportPad : public AInteractPad_Base
{
	GENERATED_BODY()

public:
	ATeleportPad();
	~ATeleportPad();
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	virtual void OnOverlapBeginBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	void ActivateDelay();
	void TeleportPlayer();
	
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category="Linked Teleport Pad") ATeleportPad* M_LinkedTeleportPad = nullptr; //the next linked teleport pad
	UPROPERTY(EditAnywhere, Category="Teleport Delay (ms)") int32 M_TeleportDelay = 100; //delay in place before allowing teleporting from this pad again
	UPROPERTY(EditAnywhere, Category="Is Active") bool M_IsTeleportActive = true;

	ACharacter* M_character = nullptr;
};
