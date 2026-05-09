// Fill out your copyright notice in the Description page of Project Settings.


#include "TKAL2ProjectileMagic.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ATKAL2ProjectileMagic::ATKAL2ProjectileMagic()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = SphereComp;
	SphereComp->SetSphereRadius(16.0f);
	SphereComp->SetCollisionProfileName("Projectile");
	
	LoopedNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LoopedNiagaraComp"));
	LoopedNiagaraComp->SetupAttachment(RootComponent);
	
	ProjMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjMoveComp"));
	ProjMoveComp->InitialSpeed = 2000.0f;
	ProjMoveComp->ProjectileGravityScale = 0.0f;
	
}

void ATKAL2ProjectileMagic::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentHit.AddDynamic(this, &ATKAL2ProjectileMagic::OnActorHit);
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ATKAL2ProjectileMagic::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// @todo: create our own damage type
	TSubclassOf<UDamageType> DmgTypeClass = UDamageType::StaticClass();
	
	UGameplayStatics::ApplyDamage(OtherActor, 10.f, GetInstigatorController(), this, DmgTypeClass);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation());

	Destroy();
}