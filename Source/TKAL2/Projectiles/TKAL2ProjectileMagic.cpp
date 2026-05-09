// Fill out your copyright notice in the Description page of Project Settings.


#include "TKAL2ProjectileMagic.h"

#include <Kismet/GameplayStatics.h>

#include "GameFramework/ProjectileMovementComponent.h"




// Sets default values
ATKAL2ProjectileMagic::ATKAL2ProjectileMagic()
{
	ProjMoveComp->InitialSpeed = 2000.0f;
}

void ATKAL2ProjectileMagic::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	
	FVector HitFromDirection = GetActorRotation().Vector();
	UGameplayStatics::ApplyPointDamage(OtherActor, 10.0f, HitFromDirection, Hit, GetInstigatorController(),
		this, DmgTypeClass);
}