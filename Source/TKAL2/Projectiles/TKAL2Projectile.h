#pragma once

#include "CoreMinimal.h"
#include <GameFramework/Actor.h>
#include "TKAL2Projectile.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class USphereComponent;
class UProjectileMovementComponent;
class UAudioComponent;

UCLASS(Abstract)
class TKAL2_API ATKAL2Projectile : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UProjectileMovementComponent> ProjMoveComp;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<USphereComponent> SphereComp;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UNiagaraComponent> LoopedNiagaraComp;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UAudioComponent> LoopedAudioComp;
	
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="Audio")
	TObjectPtr<USoundBase> ExplosionSound;
	
	UFUNCTION()      
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, const FHitResult& Hit);
	
	void PlayExplodeEffects();
	
public:
	ATKAL2Projectile();
	virtual void PostInitializeComponents() override;
};
