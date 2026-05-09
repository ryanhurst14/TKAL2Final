#pragma once

#include "CoreMinimal.h"
#include "TKAL2Projectile.h"
#include "TKAL2TeleportProjectile.generated.h"

UCLASS()
class TKAL2_API ATKAL2TeleportProjectile : public ATKAL2Projectile
{
	GENERATED_BODY()

public:
	ATKAL2TeleportProjectile();

protected:
	FTimerHandle TeleportTimer;
	
	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	float DetonateDelay = 0.2f;
	
	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	float TeleportDelay = 0.2f;
	
	void StartDelayedTeleport();
	
	void HandleTeleportation();
	
	virtual void BeginPlay() override;
	
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, const FHitResult& Hit) override;
};
