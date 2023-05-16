// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillEnable.h"
#include "MonsterAIController.h"
#include "../../BossMonster/BossMonster.h"

USkillEnable::USkillEnable()
{
}

bool USkillEnable::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AMonsterAIController* Contoroller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	if (!IsValid(Contoroller))
	{
		return false;
	}

	ABossMonster* Boss = Cast<ABossMonster>(Contoroller->GetPawn());
	if (!IsValid(Boss))
	{
		return false;
	}

	if (Boss->GetSkillEnable())
	{
		Boss->SetSkillDisEnable();
		return true;
	}

	return false;
}
