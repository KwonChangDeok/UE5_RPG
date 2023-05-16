// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PatrolWait.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API UPatrolWait : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UPatrolWait();

private:
	float PatrolWaitTime;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
