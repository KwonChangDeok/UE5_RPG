/*
BTService 클래스를 상속받아 구현한 클래스입니다.
일정 범위안에 플레이어가 존재하는지 OverlapMultiByChannel 함수를 이용해 판단한 후 
비헤이비어트리의 블랙보드에 탐지한 객체를 전달해주는 기능을 합니다.
*/
#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTService.h"
#include "TargetDetect.generated.h"


UCLASS()
class ASSASSIN_API UTargetDetect : public UBTService
{
	GENERATED_BODY()
public:
	UTargetDetect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
