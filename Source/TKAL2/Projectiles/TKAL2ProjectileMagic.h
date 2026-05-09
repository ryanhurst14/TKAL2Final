// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TKAL2Projectile.h"
#include "GameFramework/Actor.h"
#include "TKAL2ProjectileMagic.generated.h"

class UNiagaraSystem;

UCLASS(Abstract)
class TKAL2_API ATKAL2ProjectileMagic : public ATKAL2Projectile
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TSubclassOf<UDamageType> DmgTypeClass;

	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, const FHitResult& Hit) override;
public:
	ATKAL2ProjectileMagic();
	
};
