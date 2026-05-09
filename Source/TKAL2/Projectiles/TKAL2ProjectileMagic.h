// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TKAL2ProjectileMagic.generated.h"

UCLASS()
class TKAL2_API ATKAL2ProjectileMagic : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATKAL2ProjectileMagic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
