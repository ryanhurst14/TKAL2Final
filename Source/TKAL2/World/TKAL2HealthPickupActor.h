#pragma once

#include "CoreMinimal.h"
#include "TKAL2PickupActor.h"
#include "TKAL2HealthPickupActor.generated.h"

UCLASS(Abstract)
class TKAL2_API ATKAL2HealthPickupActor : public ATKAL2PickupActor
{
	GENERATED_BODY()

public:
	ATKAL2HealthPickupActor();
	
	
protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;
	
	UPROPERTY(EditDefaultsOnly, Category="Pickup")
	TObjectPtr<USoundBase> PickupSound;
	
	UPROPERTY(EditDefaultsOnly, Category="Pickup")
	float HealingAmount = 50.0f;
	
	virtual void OnActorOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	

};
