// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TKAL2AIController.generated.h"

/**
 * 
 */
UCLASS()
class TKAL2_API ATKAL2AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATKAL2AIController();
	virtual void BeginPlay() override;
};
