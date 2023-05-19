// BTDecorator 클래스를 상속받아 몬스터와 플레이어 사이의 거리를 계산해 탐지범위 내 플레이어의 존재여부를 반환하는 클래스입니다.

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
