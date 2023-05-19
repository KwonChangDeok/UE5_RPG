// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BossWait.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API UBossWait : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBossWait();

private:
	float WaitTime;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
