// BTDecorator Ŭ������ ��ӹ޾� ���Ϳ� �÷��̾� ������ �Ÿ��� ����� Ž������ �� �÷��̾��� ���翩�θ� ��ȯ�ϴ� Ŭ�����Դϴ�.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "CheckDistance.generated.h"

UENUM(BlueprintType)
enum class ECheckDistanceType : uint8
{
	Attack,
	Trace
};

/**
 * 
 */
UCLASS()
class ASSASSIN_API UCheckDistance : public UBTDecorator
{
	GENERATED_BODY()
public:
	UCheckDistance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	ECheckDistanceType	mCheckType;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};
