#pragma once

#include "CoreMinimal.h"
#include <Components/ActorComponent.h>
#include "TKAL2InteractionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TKAL2_API UTKAL2InteractionComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	float InteractionRadius = 500;
	
	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	float DistToWeightScale = 2.0f;
	
	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	float DirectionWeightScale = 1.0f;
	
	UPROPERTY()
	TObjectPtr<AActor> SelectedActor;
	
public:
	
	void Interact();
	
	UTKAL2InteractionComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
