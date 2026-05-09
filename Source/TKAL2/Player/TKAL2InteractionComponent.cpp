
#include "TKAL2InteractionComponent.h"

#include "../../../Intermediate/ProjectFiles/TKAL2GameTypes.h"
#include "Engine/OverlapResult.h"
#include "Core/TKAL2InteractionInterface.h"

TAutoConsoleVariable<bool> CVarInteractionDebugDrawing(TEXT("game.interaction.DebugDraw"), false,
	TEXT("Enable interacation component debug rendering (0 = off, 1 = on"), ECVF_Cheat);

UTKAL2InteractionComponent::UTKAL2InteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTKAL2InteractionComponent::Interact()
{
	//Get the interaction interface of the best item and call interact()
	/*ITKAL2InteractionInterface* InteractionInterface = Cast<ITKAL2InteractionInterface>(SelectedActor);
	if (InteractionInterface)
	{a
		InteractionInterface->Interact();
	}*/
	
	ITKAL2InteractionInterface::Execute_Interact(SelectedActor);
}

void UTKAL2InteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//Get player controller and access to player
	APlayerController* PC = CastChecked<APlayerController>(GetOwner());
	FVector Center = PC->GetPawn()->GetActorLocation();
	FVector CameraLocation = PC->PlayerCameraManager->GetCameraLocation();
	ECollisionChannel CollisionChannel = COLLISION_INTERACTION;
	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);
	
	//Get all overlaps with interaction radius
	TArray<FOverlapResult> Overlaps;
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);
	
	float HighestWeight = 0;
	float InteractionRadiusSqrd = InteractionRadius * InteractionRadius;
	
	AActor* BestActor = nullptr;
	
	bool bEnabledDebugDraw = CVarInteractionDebugDrawing.GetValueOnGameThread();
	
	for (FOverlapResult& Overlap : Overlaps)
	{
		
		FVector Origin;
		FVector BoxExtends;
		Overlap.GetActor()->GetActorBounds(true, Origin, BoxExtends);
		
		//Show overlap with interaction radius
		//FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();
		//Get dot product 
		FVector OverlapDirection = (Origin - CameraLocation).GetSafeNormal();
		
		float DistanceTo = (Origin - Center).SizeSquared();
		float NormDistanceTo = 1.0f - (DistanceTo / InteractionRadiusSqrd);
		
		float DotResult = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());
		float NormDotResult = DotResult * 0.5 + 0.5f; //Norm to 0.0f to 1.0f
		
		//Get the best dot so far 
		float Weight = (NormDotResult * DirectionWeightScale) + (NormDistanceTo * DistToWeightScale);
		if (Weight > HighestWeight)
		{
			BestActor = Overlap.GetActor();
			HighestWeight = Weight;
		}
		
		if (bEnabledDebugDraw)
		{
			DrawDebugBox(GetWorld(), Origin, FVector(50.0f), FColor::Red);
			FString DebugString = FString::Printf(TEXT("Weight: %f, Dot: %f, Dist: %f"), Weight, NormDotResult, NormDistanceTo);
			DrawDebugString(GetWorld(), Origin, DebugString, nullptr, FColor::White, 0.0f, true);
		}
	}
	
	SelectedActor = BestActor;
	
	if (bEnabledDebugDraw)
	{
		if (BestActor != nullptr)
		{
			DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(50.0f), FColor::Green);
		}
		
		DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);
	}
	
	

}

