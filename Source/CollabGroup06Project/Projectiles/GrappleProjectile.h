#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrappleProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class COLLABGROUP06PROJECT_API AGrappleProjectile : public AActor
{
	GENERATED_BODY()

public:
	AGrappleProjectile();

	/** Sphere collision component **/
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

protected:
	virtual void BeginPlay() override;

	/** called when projectile hits something **/
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};