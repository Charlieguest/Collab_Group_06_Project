#pragma once

#include "CoreMinimal.h"
#include "CharacterTool_Base.h"
#include "CollabGroup06Project/Interfaces/Fireable.h"
#include "CharacterTool_GrappleGun.generated.h"

class ABerryPickup;
class AGrappleProjectile;
class UArrowComponent;
class UCableComponent;
class APlayerBerry;

UCLASS()
class COLLABGROUP06PROJECT_API ACharacterTool_GrappleGun : public ACharacterTool_Base
{
	GENERATED_BODY()

public:
	ACharacterTool_GrappleGun();
	
	virtual bool Fire_Implementation(FVector Forward) override;

	virtual void Fire_Stop_Implementation() override;

	virtual void Grapple_Aim_Implementation(APlayerCharacter* player) override;

	virtual void Grapple_Aim_Released_Implementation(APlayerCharacter* player) override;

	virtual void RemoveBerry_Implementation() override;

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void GrapplePlayer();
	
	UFUNCTION()
	void GrappleBerry(ABerryPickup* BerryPickup);

	UFUNCTION()
	void AttachBerry();

	void DestroyGrappleProjectile();

	UFUNCTION()
	void RemoveBerry();

	UFUNCTION()
	void InitialProjectileTimer();
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _Root;

	/* ------------------------ */
	/* ------------------------ */
	/* -----PROJECTILE VARS---- */
	/* ------------------------ */
	/* ------------------------ */

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AGrappleProjectile> _ProjectileRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool _HasFired;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _ProjectileSpeed = 10000.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _MaxFireDistance = 1000.0f;
	
	FTimerHandle _InitialProjectileTimerHandle;

	/* ------------------------ */
	/* ------------------------ */
	/* -----GRAPPLE VARS------- */
	/* ------------------------ */
	/* ------------------------ */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = cable, meta = (AllowPrivateAccess = "true"))
	UCableComponent* _Cable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector _ProjectileHitLoc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool _IsGrapplingPlayer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool _IsGrapplingBerry;

	TObjectPtr<AGrappleProjectile> _GrappleProjectile;
	
	FTimerHandle _PlayerGrappleTimer;
	FTimerDelegate _BerryGrappleTimerDelegate;
	FTimerHandle _BerryGrappleTimer;

	/* ------------------------ */
	/* ------------------------ */
	/* --- BERRY ATTACH VARS -- */
	/* ------------------------ */
	/* ------------------------ */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "True"))
	TObjectPtr<UArrowComponent> _BerryAttachPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _HasBerry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _GrappleForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TSubclassOf<APlayerBerry> _AttachedBerryRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<APlayerBerry> _AttachedBerry;
};
