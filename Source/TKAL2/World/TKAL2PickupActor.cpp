
#include "TKAL2PickupActor.h"

#include <Components/SphereComponent.h>

ATKAL2PickupActor::ATKAL2PickupActor()
{
	OverlapComp = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapComp"));
	OverlapComp->SetSphereRadius(130.0f);
	RootComponent = OverlapComp;
}

void ATKAL2PickupActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnActorOverlapped);
}

void ATKAL2PickupActor::OnActorOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Do nothing
}
