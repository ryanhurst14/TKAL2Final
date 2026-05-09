#include "TKAL2PlayerController.h"

#include <EnhancedInputComponent.h>

#include "TKAL2InteractionComponent.h"

ATKAL2PlayerController::ATKAL2PlayerController()
{
	InteractionComp = CreateDefaultSubobject<UTKAL2InteractionComponent>(TEXT("InteractionComp"));
	
}

void ATKAL2PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInput->BindAction(Input_Interact, ETriggerEvent::Triggered, this, &ATKAL2PlayerController::StartInteract);
}

void ATKAL2PlayerController::StartInteract()
{
	InteractionComp->Interact();
}