// BTTaskNode 클래스를 상속받아 몬스터의 정찰 기능을 구현한 클래스입니다.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Patrol.generated.h"

UCLASS()
class ASSASSIN_API UPatrol : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UPatrol();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
