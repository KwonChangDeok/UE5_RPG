// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTService.h"
#include "TargetDetect.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API UTargetDetect : public UBTService
{
	GENERATED_BODY()
public:
	UTargetDetect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
