// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "LichSkill.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API ULichSkill : public UBTTaskNode
{
	GENERATED_BODY()
public:
	ULichSkill();

private:
	bool IsBerserk;
	
	class ALich* Boss;

	int32 SkillNum;

	FTimerHandle Skill1Timer;
	FTimerHandle Skill1Fade;

	int32 RandTime;

	class ACharacter* Target;

	bool Skill1Key;

	bool Skill4Key;

	float AccDelta;

	class ADecal* Decal;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

public:
	void Fade();

	void Skill1Teleport();

	void Skill4Move(float DeltaTime);
};
