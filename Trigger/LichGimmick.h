/*
BoxTriggerBase 클래스를 상속받아 리치의 HP가 0일때, 30초 내에 플레이어가 체력 1인 상태로 오버랩 이벤트를 발생시키면 
아웃트로 영상을 재생하며 리치가 소멸되도록 동작합니다.
*/

#pragma once

#include "BoxTriggerBase.h"
#include "LichGimmick.generated.h"

UCLASS()
class ASSASSIN_API ALichGimmick : public ABoxTriggerBase
{
	GENERATED_BODY()
public:
	ALichGimmick();

public:
	virtual void TriggerBegin(const FHitResult& SweepResult);
};
