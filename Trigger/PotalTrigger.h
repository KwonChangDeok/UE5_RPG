// BoxTriggerBase 클래스를 상속받아 오버랩시 레벨전환을 구현한 클래스입니다. 
// 에디터상에서 파티클시스템과 이동할 레벨명을 설정할 수 있도록 구현했습니다.

#pragma once

#include "BoxTriggerBase.h"
#include "PotalTrigger.generated.h"

UCLASS()
class ASSASSIN_API APotalTrigger : public ABoxTriggerBase
{
	GENERATED_BODY()
public:
	APotalTrigger();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FName mLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UParticleSystemComponent* ParticleSystemComponent;

public:
	virtual void TriggerBegin(const FHitResult& SweepResult);
};
