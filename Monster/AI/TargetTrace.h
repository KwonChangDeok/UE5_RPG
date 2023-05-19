/*
BTTaskNode 클래스를 상속받아 몬스터의 추적기능을 구현한 클래스입니다.
몬스터는 인식한 플레이어를 추적하며, 공격 사정거리 안에 들어온다면 공격하고 
탐지범위를 벗어난다면 원래의 로직을 수행하도록 하는 기능을 합니다.
*/

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TargetTrace.generated.h"

UCLASS()
class ASSASSIN_API UTargetTrace : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTargetTrace();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
