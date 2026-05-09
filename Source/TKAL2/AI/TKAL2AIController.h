// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TKAL2AIController.generated.h"

/**
 * 
 */

class UBehaviorTree;
UCLASS()
class TKAL2_API ATKAL2AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATKAL2AIController();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviourTree;
	
	virtual void BeginPlay() override;

};
