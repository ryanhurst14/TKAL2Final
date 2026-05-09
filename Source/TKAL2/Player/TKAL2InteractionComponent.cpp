
#include "TKAL2InteractionComponent.h"

#include "../../../Intermediate/ProjectFiles/TKAL2GameTypes.h"
#include "Engine/OverlapResult.h"
#include "Core/TKAL2InteractionInterface.h"



UTKAL2InteractionComponent::UTKAL2InteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTKAL2InteractionComponent::Interact()
{
	//Get the interaction interface of the best item and call interact()
	ITKAL2InteractionInterface* InteractionInterface = Cast<ITKAL2InteractionInterface>(SelectedActor);
	if (InteractionInterface)
	{
		InteractionInterface->Interact();
	}
}

void UTKAL2InteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//Get player controller and access to player
	APlayerController* PC = CastChecked<APlayerController>(GetOwner());
	FVector Center = PC->GetPawn()->GetActorLocation();
	
	ECollisionChannel CollisionChannel = COLLISION_INTERACTION;
	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);
	
	//Get all overlaps with interaction radius
	TArray<FOverlapResult> Overlaps;
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);
	
	float HighestDot = -1.0;
	AActor* BestActor = nullptr;
	
	for (FOverlapResult& Overlap : Overlaps)
	{
		//Show overlap with interaction radius
		FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();
		//Get dot product 
		
		
		FVector OverlapDirection = (OverlapLocation - Center).GetSafeNormal();
		float DotResult = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());
		
		//Get the best dot so far 
		if (DotResult > HighestDot)
		{
			BestActor = Overlap.GetActor();
			HighestDot = DotResult;
		}
		
		DrawDebugBox(GetWorld(), OverlapLocation, FVector(50.0f), FColor::Red);
		FString DebugString = FString::Printf(TEXT("Dot: %f"), DotResult);
		DrawDebugString(GetWorld(), OverlapLocation, DebugString, nullptr, FColor::White, 0.0f, true);
	}
	
	if (BestActor != nullptr)
	{
		SelectedActor = BestActor;
		DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(50.0f), FColor::Green);
	}
	
	DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);

}

