


#include "TKAL2TeleportProjectile.h"

#include <NiagaraComponent.h>
#include <Components/AudioComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>


ATKAL2TeleportProjectile::ATKAL2TeleportProjectile()
{
	ProjMoveComp->InitialSpeed = 6000.0f;
}

void ATKAL2TeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TeleportTimer, this, &ThisClass::StartDelayedTeleport, DetonateDelay);
}

void ATKAL2TeleportProjectile::StartDelayedTeleport()
{
	PlayExplodeEffects();
	
	ProjMoveComp->StopMovementImmediately();
	LoopedNiagaraComp->Deactivate();
	LoopedAudioComp->Stop();
	SetActorTickEnabled(false);
	
	GetWorldTimerManager().SetTimer(TeleportTimer, this, &ThisClass::HandleTeleportation, TeleportDelay);

}

void ATKAL2TeleportProjectile::HandleTeleportation()
{
	APawn* ActorToTeleport = GetInstigator();
	check(ActorToTeleport != nullptr);
	
	ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation());
	
	Destroy();
}

void ATKAL2TeleportProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)																	
{
	//Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	GetWorldTimerManager().ClearTimer(TeleportTimer);
	StartDelayedTeleport();																																									
}
