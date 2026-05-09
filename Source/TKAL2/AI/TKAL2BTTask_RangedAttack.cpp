// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TKAL2BTTask_RangedAttack.h"

#include "AIController.h"
#include "../../../Intermediate/ProjectFiles/TKAL2GameTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "Projectiles/TKAL2Projectile.h"

UTKAL2BTTask_RangedAttack::UTKAL2BTTask_RangedAttack()
{
	TargetActorKey.SelectedKeyName = NAME_TargetActor;
}

EBTNodeResult::Type UTKAL2BTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* Pawn = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	check(Pawn)
	
	FVector SpawnLocation = Pawn->GetMesh()->GetSocketLocation(MuzzleSocketName);
	
	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName));
	if (!IsValid(TargetActor))
	{
		return EBTNodeResult::Failed;
	}
	
	FVector Direction = TargetActor->GetActorLocation() - SpawnLocation;
	FRotator SpawnRotation = Direction.Rotation();
	SpawnRotation.Pitch += FMath::RandRange(0.0f, MaxBulletSpread);
	SpawnRotation.Yaw += FMath::RandRange(-MaxBulletSpread, MaxBulletSpread);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Pawn;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	AActor* NewProj = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	
	return NewProj ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}


