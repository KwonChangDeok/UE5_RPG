// BoxTriggerBase Ŭ������ ��ӹ޾� �������� ������ȯ�� ������ Ŭ�����Դϴ�. 
// �����ͻ󿡼� ��ƼŬ�ý��۰� �̵��� �������� ������ �� �ֵ��� �����߽��ϴ�.

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
