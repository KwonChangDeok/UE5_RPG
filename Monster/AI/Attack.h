// BTTaskNode 클래스를 상속받아 몬스터의 기본공격을 구현한 클래스입니다.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Attack.generated.h"

UCLASS()
class ASSASSIN_API UAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
