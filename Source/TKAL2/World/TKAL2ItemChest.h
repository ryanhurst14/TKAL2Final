#pragma once

#include "CoreMinimal.h"
#include <GameFramework/Actor.h>

#include "TKAL2/Core/TKAL2InteractionInterface.h"
#include "TKAL2ItemChest.generated.h"

class UStaticMeshComponent;


UCLASS()
class TKAL2_API ATKAL2ItemChest : public AActor, public ITKAL2InteractionInterface
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> BaseMeshComp;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> LidMeshComp;

	UPROPERTY(EditAnywhere, Category="Animation")
	float AnimationSpeed = 50.0f;
	
	UPROPERTY(EditAnywhere, Category="Animation")
	float AnimationTargetPitch = 120.0f;
	float CurrentAnimationPitch = 0.0f;
	
public:
	virtual void Interact() override;
	
	ATKAL2ItemChest();
	virtual void Tick( float DeltaTime ) override;
	
};
