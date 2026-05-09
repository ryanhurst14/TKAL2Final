// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TKAL2BTTask_RangedAttack.generated.h"

class ATKAL2Projectile;
/**
 * 
 */
UCLASS()
class TKAL2_API UTKAL2BTTask_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere, Category="AI")
	FName MuzzleSocketName;
	
	UPROPERTY(EditAnywhere, Category="AI")
	FBlackboardKeySelector TargetActorKey;
	
	UPROPERTY(EditAnywhere, Category="AI")
	TSubclassOf<ATKAL2Projectile> ProjectileClass;
	
	UPROPERTY(EditAnywhere, Category="AI")
	float MaxBulletSpread = 5.0f;
	
	UTKAL2BTTask_RangedAttack();
};
