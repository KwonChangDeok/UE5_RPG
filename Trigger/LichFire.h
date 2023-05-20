// BoxTriggerBase 클래스를 상속받아 리치 맵에서 오버랩시 초당 플레이어의 HP가 1씩 감소하도록 구현했으며,
// 기믹 파훼를 위한 도구로 활용할 수 있습니다.

#pragma once

#include "BoxTriggerBase.h"
#include "LichFire.generated.h"

UCLASS()
class ASSASSIN_API ALichFire : public ABoxTriggerBase
{
	GENERATED_BODY()
public:
	ALichFire();

private:
	FTimerHandle FireTimer;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UParticleSystemComponent* ParticleSystemComponent;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void TriggerBegin(const FHitResult& SweepResult);
	virtual void TriggerEnd();

public:
	void Fire();
};
