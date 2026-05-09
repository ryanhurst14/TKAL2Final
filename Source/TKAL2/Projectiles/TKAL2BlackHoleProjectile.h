#pragma once

#include "CoreMinimal.h"
#include "TKAL2Projectile.h"
#include "TKAL2BlackHoleProjectile.generated.h"

class URadialForceComponent;

UCLASS(Abstract)
class TKAL2_API ATKAL2BlackHoleProjectile : public ATKAL2Projectile
{
	GENERATED_BODY()

public:
	ATKAL2BlackHoleProjectile();
	virtual void PostInitializeComponents() override;
protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<URadialForceComponent> RadialForceComp;
	
	UFUNCTION()
	void OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
