

#pragma once

#include "CoreMinimal.h"
#include <GameFramework/PlayerController.h>
#include "TKAL2PlayerController.generated.h"
class UInputAction;
class UTKAL2InteractionComponent;
/**
 * 
 */
UCLASS()
class TKAL2_API ATKAL2PlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UTKAL2InteractionComponent> InteractionComp;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Interact;
	
	void StartInteract();
	virtual void SetupInputComponent() override;
	
public:
	ATKAL2PlayerController();
};
