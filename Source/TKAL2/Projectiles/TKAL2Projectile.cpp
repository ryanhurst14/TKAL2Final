


#include "TKAL2Projectile.h"

#include <NiagaraComponent.h>
#include <NiagaraFunctionLibrary.h>
#include <Components/AudioComponent.h>
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>


ATKAL2Projectile::ATKAL2Projectile()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = SphereComp;
	SphereComp->SetSphereRadius(16.0f);
	SphereComp->SetCollisionProfileName("Projectile");
	
	ProjMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjMoveComp"));
	ProjMoveComp->InitialSpeed = 2000.0f;
	ProjMoveComp->ProjectileGravityScale = 0.0f;
	
	LoopedNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LoopedNiagaraComp"));
	LoopedNiagaraComp->SetupAttachment(SphereComp);
	
	LoopedAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("LoopedAudioComp"));
	LoopedAudioComp->SetupAttachment(SphereComp);
}

void ATKAL2Projectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentHit.AddDynamic(this, &ATKAL2Projectile::OnActorHit);
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}



void ATKAL2Projectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	PlayExplodeEffects();
	Destroy();
}

void ATKAL2Projectile::PlayExplodeEffects()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation());

	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation(), 
		FRotator::ZeroRotator);
}

