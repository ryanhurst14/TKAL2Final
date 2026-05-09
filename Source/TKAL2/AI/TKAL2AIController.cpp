// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TKAL2AIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

ATKAL2AIController::ATKAL2AIController()
{
	
}

void ATKAL2AIController::BeginPlay()
{
	Super::BeginPlay();
	
	RunBehaviorTree(BehaviourTree);
	
	FName TargetActor = FName("TargetActor");
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	check(PlayerPawn);
	
	GetBlackboardComponent()->SetValueAsObject(TargetActor, PlayerPawn);
}


