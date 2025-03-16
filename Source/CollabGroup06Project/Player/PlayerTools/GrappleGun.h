#pragma once

#include "CoreMinimal.h"
#include "InteractiveToolObjects.h"
#include "CollabGroup06Project/Interfaces/Fireable.h"
#include "GrappleGun.generated.h"

class ABerryPickup;
class AGrappleProjectile;
class UArrowComponent;
class UCableComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGrappleStartSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGrappleDuringSignature, FVector, GrapPoint);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGrappleEndSignature);

UCLASS()
class COLLABGROUP06PROJECT_API AGrappleGun : public AActor, public IFireable
{
	GENERATED_BODY()

public:
	AGrappleGun();
	
	virtual bool Fire_Implementation(FVector Forward) override;

	virtual void Fire_Stop_Implementation() override;

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void GrapplePlayer();
	
	UFUNCTION()
	void GrappleBerry(ABerryPickup* BerryPickup);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AGrappleProjectile> _ProjectileRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _Root;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> _BerryAttachPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool _HasFired;

	int _FireTime = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _ProjectileSpeed = 10000.0f;

	/* ------------------------ */
	/* ------------------------ */
	/* -----GRAPPLE VARS------- */
	/* ------------------------ */
	/* ------------------------ */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = cable, meta = (AllowPrivateAccess = "true"))
	UCableComponent* _Cable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float _MaxDistance = 1600.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector _ProjectileHitLoc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool _IsGrappling;

	TObjectPtr<AGrappleProjectile> _GrappleProjectile;

	FGrappleStartSignature OnGrappleStart;
	FGrappleDuringSignature OnGrappleDuring;
	FGrappleEndSignature OnGrappleEnd;

	FTimerHandle _PlayerGrappleTimer;
	FTimerDelegate _BerryGrappleTimerDelegate;
	FTimerHandle _BerryGrappleTimer;
	
};
