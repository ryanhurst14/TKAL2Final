


#include "TKAL2ItemChest.h"


ATKAL2ItemChest::ATKAL2ItemChest()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
	BaseMeshComp->SetCollisionProfileName("Interaction");
	RootComponent = BaseMeshComp;
	
	LidMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMeshComp"));
	LidMeshComp->SetCollisionProfileName("NoCollision");
	LidMeshComp->SetupAttachment(BaseMeshComp);
	
}

void ATKAL2ItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CurrentAnimationPitch = FMath::FInterpConstantTo(CurrentAnimationPitch, AnimationTargetPitch, DeltaTime,  AnimationSpeed);
	LidMeshComp->SetRelativeRotation(FRotator(CurrentAnimationPitch, 0, 0));
	
	if (FMath::IsNearlyEqual(CurrentAnimationPitch,AnimationTargetPitch))
	{
		SetActorTickEnabled(false);
	}
}


void ATKAL2ItemChest::Interact()
{
	//Play Anim
	SetActorTickEnabled(true);
}
