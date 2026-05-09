// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TKAL2EnvQueryContext_TargetActor.h"

#include "AIController.h"
#include "../../../Intermediate/ProjectFiles/TKAL2GameTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UTKAL2EnvQueryContext_TargetActor::ProvideContext(FEnvQueryInstance& QueryInstance,
                                                       FEnvQueryContextData& ContextData) const
{
	APawn* QuerierObject = Cast<APawn>(QueryInstance.Owner.Get());
	if (ensure(QuerierObject))
	{
		AAIController* Controller = Cast<AAIController>(QuerierObject->GetController());
		check(Controller);
		AActor* TargetObject = 
			Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(NAME_TargetActor));
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, TargetObject);
	}
	
}
