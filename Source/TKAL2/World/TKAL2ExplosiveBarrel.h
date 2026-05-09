#pragma once

#include "CoreMinimal.h"
#include <GameFramework/Actor.h>
#include "TKAL2ExplosiveBarrel.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class URadialForceComponent;
class UStaticMeshComponent;
class UStaticMesh;
class USoundBase;
class UAudioComponent;


UCLASS()
class TKAL2_API ATKAL2ExplosiveBarrel : public AActor
{
	GENERATED_BODY()

protected:
	// Sets default values for this actor's properties
	bool bHasExploded;
	const float ExplosionDelayTime = 3.0f;
	FTimerHandle ExplodeTimerHandle;
	
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> ActiveBurningEffectComp = nullptr;
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> ActiveBurningSoundComp = nullptr	;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UStaticMesh> StaticMesh;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<URadialForceComponent> ImpulseComp;
	
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	TObjectPtr<USoundBase> BurningSound;
	
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	TObjectPtr<USoundBase> ExplosionSound;
	
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> BurningEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	void ExplodeTimerElapsed();
	
	
public:
	ATKAL2ExplosiveBarrel();
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
