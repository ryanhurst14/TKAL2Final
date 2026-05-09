


#include "TKAL2HealthPickupActor.h"

#include <Components/SphereComponent.h>
#include <Kismet/GameplayStatics.h>

#include "ActionSystem/TKAL2ActionSystemComponent.h"


ATKAL2HealthPickupActor::ATKAL2HealthPickupActor()
{
	OverlapComp->SetCollisionProfileName("Pickups");
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	StaticMeshComp->SetCollisionProfileName("NoCollision");
	StaticMeshComp->SetupAttachment(RootComponent);
}

void ATKAL2HealthPickupActor::OnActorOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Does nothing anyways
	//Super::OnActorOverlapped(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	UTKAL2ActionSystemComponent* ActionComp = 
		OtherActor->GetComponentByClass<UTKAL2ActionSystemComponent>();
	
	if (ensure(ActionComp) && !ActionComp->IsFullHealth())
	{
		ActionComp->ApplyHealthChange(HealingAmount);
		
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation(),
			FRotator::ZeroRotator);
		
		Destroy();
	}
		
}

