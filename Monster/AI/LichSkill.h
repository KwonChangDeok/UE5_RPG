// BTTaskNode 클래스를 상속받아 리치 몬스터의 스킬을 실행하도록 구현한 클래스입니다. 랜덤한 값과 조건들에 따른 스킬을 선택해 실행합니다.

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
