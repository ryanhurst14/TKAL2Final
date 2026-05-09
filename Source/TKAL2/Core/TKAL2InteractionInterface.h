#pragma once

#include "CoreMinimal.h"
#include <UObject/Interface.h>
#include "TKAL2InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UTKAL2InteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Attach to things you want to interact with and it will provide some virtual interact function
 */
class TKAL2_API ITKAL2InteractionInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent)
	void Interact();
};