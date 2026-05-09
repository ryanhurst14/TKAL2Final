#pragma once

#include "CoreMinimal.h"
#include <Components/ActorComponent.h>
#include "TKAL2ActionSystemComponent.generated.h"

USTRUCT(BlueprintType)
struct FTKAL2AttributeSet
{
	
	GENERATED_BODY()
	
	FTKAL2AttributeSet(): 
		Health(100.0f),																					
		MaxHealth(100.0f) {}
																								
	UPROPERTY(BlueprintReadOnly)
	float Health;
	
	UPROPERTY(BlueprintReadOnly)
	float MaxHealth;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TKAL2_API UTKAL2ActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTKAL2ActionSystemComponent();
	void ApplyHealthChange(float InValueChange);
	bool IsFullHealth() const;
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
protected:
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FTKAL2AttributeSet Attributes;
};
