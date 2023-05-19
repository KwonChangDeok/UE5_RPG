// BTTaskNode 클래스를 상속받아 보스몬스터의 대기 행동을 구현한 클래스입니다. 보스몬스터 종류별로 일정시간 Idle상태로 대기하도록 동작합니다.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BossWait.generated.h"

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
