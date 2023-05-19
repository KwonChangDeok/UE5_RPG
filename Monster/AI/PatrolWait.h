// BTTaskNode 클래스를 상속받아 몬스터가 정찰 중 실정시간 Idle상태로 대기하는 기능을 구현한 클래스입니다.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PatrolWait.generated.h"

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
