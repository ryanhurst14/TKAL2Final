


#include "TKAL2BlackHoleProjectile.h"

#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <PhysicsEngine/RadialForceComponent.h>


ATKAL2BlackHoleProjectile::ATKAL2BlackHoleProjectile()
{
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetupAttachment(RootComponent);
	RadialForceComp->ForceStrength = -800000.0f;
	RadialForceComp->Radius = 1200.0f;
	
	RadialForceComp->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	
	SphereComp->SetSphereRadius(20.0f);
	SphereComp->SetCollisionProfileName(TEXT("BlackholeCore"));
	
	ProjMoveComp->InitialSpeed = 500.0f;
	InitialLifeSpan = 5.0f;
	
}

void ATKAL2BlackHoleProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATKAL2BlackHoleProjectile::OnSphereOverlappedActor);
	
}

void ATKAL2BlackHoleProjectile::OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
}

