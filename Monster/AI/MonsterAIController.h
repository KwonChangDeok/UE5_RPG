// AIController Ŭ������ ��ӹ޾� ���� ������ ���� �����̺��Ʈ���� �����嵥���͸� �ε��ϴ� ����� �����մϴ�.

// ���� AI�� ������ ��, ���� �Ѹ����� �׽�Ʈ �� ���������� �����ϳ�, �ټ��� ���͸� ��ġ�ϸ� ������ �޾����ϴ�.
// �̴� ��� ���Ͱ� ���� �׽�ũ��带 �����ϱ� ������(�ּҸ� ����� ��� �����߽��ϴ�.) �߻��� ��������
// �̸� ���� ��������� �Լ��� ����ؼ� �ȵȴٴ� �Ͱ� ��ü���� �����ؾ� �� ������ �����带 �̿��ؾ� �Ѵٴ� ���� �������ϴ�.
// ���� ��Ȯ�� ���� ���� ���δ�� ������ �Ϸ��� ���� ������� ������, õõ�� ħ���ϰ� ���� ���� ���� ������ �ִٴ� ���� �������ϴ�.

#pragma once

#include "../../GameInfo.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

UCLASS()
class ASSASSIN_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMonsterAIController();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UBehaviorTree* mBehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UBlackboardData* mBlackboardData;

protected:
	virtual void OnPossess(APawn* aPawn) override;

public:
	void SetBehaviorTree(const FString& Path);
	void SetBlackboard(const FString& Path);
};
