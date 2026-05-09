#pragma once

#include "CoreMinimal.h"
#include <GameFramework/Actor.h>
#include "TKAL2PickupActor.generated.h"

class USphereComponent;

UCLASS(Abstract)
class TKAL2_API ATKAL2PickupActor : public AActor
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;
	ATKAL2PickupActor();
	
protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<USphereComponent> OverlapComp;
	
	UFUNCTION()
	virtual void OnActorOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
