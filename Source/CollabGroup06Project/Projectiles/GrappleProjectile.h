#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrappleProjectile.generated.h"

class APlayerBerry;
class USphereComponent;
class UProjectileMovementComponent;
class UArrowComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRemoveBerrySignature);

UCLASS()
class COLLABGROUP06PROJECT_API AGrappleProjectile : public AActor
{
	GENERATED_BODY()

public:
	AGrappleProjectile();
	
	void AttachBerryProjectile();
	
	/** Sphere collision component **/
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	FRemoveBerrySignature OnRemoveBerry;

protected:
	virtual void BeginPlay() override;

	/** called when projectile hits something **/
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/* ------------------------ */
	/* ------------------------ */
	/* --- BERRY ATTACH VARS -- */
	/* ------------------------ */
	/* ------------------------ */
	
	bool _ProjectileHasBerry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "True"))
	TObjectPtr<UArrowComponent> _BerryAttachPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TSubclassOf<APlayerBerry> _AttachedBerryRef;
};