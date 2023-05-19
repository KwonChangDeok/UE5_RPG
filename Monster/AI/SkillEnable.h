// BTDecorator 클래스를 상속받아 보스몬스터가 현재 스킬을 사용가능한 상태인지 반환하는 기능을 수행합니다.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "SkillEnable.generated.h"

UCLASS()
class ASSASSIN_API USkillEnable : public UBTDecorator
{
	GENERATED_BODY()
public:
	USkillEnable();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};
