// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "SkillEnable.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API USkillEnable : public UBTDecorator
{
	GENERATED_BODY()
public:
	USkillEnable();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};
