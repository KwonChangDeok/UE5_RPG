/*
BTTaskNode Ŭ������ ��ӹ޾� ������ ��������� ������ Ŭ�����Դϴ�.
���ʹ� �ν��� �÷��̾ �����ϸ�, ���� �����Ÿ� �ȿ� ���´ٸ� �����ϰ� 
Ž�������� ����ٸ� ������ ������ �����ϵ��� �ϴ� ����� �մϴ�.
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
