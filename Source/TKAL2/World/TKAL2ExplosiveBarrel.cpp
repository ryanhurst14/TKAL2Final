#include "TKAL2ExplosiveBarrel.h"

#include <NiagaraComponent.h>
#include <NiagaraFunctionLibrary.h>
#include <Components/AudioComponent.h>
#include <Kismet/GameplayStatics.h>
#include "PhysicsEngine/RadialForceComponent.h"


ATKAL2ExplosiveBarrel::ATKAL2ExplosiveBarrel()
{
	//Need Static Mesh + Comp
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	RootComponent = StaticMeshComp;
	StaticMeshComp->SetStaticMesh(StaticMesh);
	StaticMeshComp->SetSimulatePhysics(true);
	
	//Impulse Component Settings
	ImpulseComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("ImpulseComp"));
	ImpulseComp->SetupAttachment(RootComponent);
	ImpulseComp->bIgnoreOwningActor = true;
	ImpulseComp->ImpulseStrength = 500000.0f;
	ImpulseComp->Radius = 750.0f;
	ImpulseComp->bAutoActivate = true;
	
	bHasExploded = false;
}

float ATKAL2ExplosiveBarrel::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	//Check if it has exploded, and if there is timer active for exploding it
	if (!bHasExploded && !GetWorldTimerManager().IsTimerActive(ExplodeTimerHandle))
	{
		//Play the burning effect attached to the barrel
		ActiveBurningEffectComp = UNiagaraFunctionLibrary::SpawnSystemAttached(BurningEffect, StaticMeshComp, FName("Burning Effect"), 
			FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
		//Play the sound attached to barrel
		ActiveBurningSoundComp = UGameplayStatics::SpawnSoundAttached(BurningSound, StaticMeshComp);
		//Set 3 sec timer
		GetWorldTimerManager().SetTimer(ExplodeTimerHandle, this, &ATKAL2ExplosiveBarrel::ExplodeTimerElapsed, ExplosionDelayTime);
	}
	
	return ActualDamage;
}


void ATKAL2ExplosiveBarrel::ExplodeTimerElapsed()
{
	bHasExploded = true;
	
	ImpulseComp->FireImpulse();
	if (ActiveBurningEffectComp)
	{
		ActiveBurningEffectComp->Deactivate();
	}
	
	if (ActiveBurningSoundComp)
	{
		ActiveBurningSoundComp->Stop();
	}
	
	StaticMeshComp->AddImpulse(FVector::UpVector * 1000, NAME_None, true);
	StaticMeshComp->AddAngularImpulseInDegrees(FVector::RightVector * 1000, NAME_None, true);
	
	//Play final explosion effects and sounds	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation(), FRotator::ZeroRotator);
}

