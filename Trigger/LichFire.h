// BoxTriggerBase Ŭ������ ��ӹ޾� ��ġ �ʿ��� �������� �ʴ� �÷��̾��� HP�� 1�� �����ϵ��� ����������,
// ��� ���Ѹ� ���� ������ Ȱ���� �� �ֽ��ϴ�.

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
