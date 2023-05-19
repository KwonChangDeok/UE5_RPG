// BTDecorator Ŭ������ ��ӹ޾� �������Ͱ� ���� ��ų�� ��밡���� �������� ��ȯ�ϴ� ����� �����մϴ�.

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
