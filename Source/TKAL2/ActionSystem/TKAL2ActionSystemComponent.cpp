


#include "TKAL2ActionSystemComponent.h"


// Sets default values for this component's properties
UTKAL2ActionSystemComponent::UTKAL2ActionSystemComponent()
{
	
}

void UTKAL2ActionSystemComponent::ApplyHealthChange(float InValueChange)
{
	float OldHealth = Attributes.Health;
	
	Attributes.Health = FMath::Clamp(Attributes.Health + InValueChange, 0.0f, Attributes.MaxHealth);
	
	if (!FMath::IsNearlyEqual(OldHealth, Attributes.Health))
	{
		OnHealthChanged.Broadcast(Attributes.Health, OldHealth);
	}
	
	UE_LOG(LogTemp, Log, TEXT("New Health: %f, MaxHealth: %f"), Attributes.Health, Attributes.MaxHealth);
}

bool UTKAL2ActionSystemComponent::IsFullHealth() const
{	
	return FMath::IsNearlyEqual(Attributes.Health, Attributes.MaxHealth);
}

