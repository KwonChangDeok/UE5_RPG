/*
BTTaskNode Ŭ������ ��ӹ޾� �������� ������ ��ų�� �����ϵ��� ������ Ŭ�����Դϴ�.
���� ������ ���� ���ǿ� ���� ��ų�� ������ �����մϴ�.
������ ���� ������ �߰��ϱ� ���̶�, �̸��� �������� ���ϰ� �ۼ��߽��ϴ�.
���̹� ���� Ȯ���� ����ؾ� ���� �������ϴ�.
*/
#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UseSkill.generated.h"

// Giant�� ��ų
UCLASS()
class ASSASSIN_API UUseSkill : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UUseSkill();

private:
	ARockGiant* Boss;

	FTimerHandle LaunchTimer;

	FVector LaunchVelocity;

	int32 SkillNum;

	bool key;

	bool IsBerserk;

	class ADecal* Decal;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

public:
	void Launch();
};
