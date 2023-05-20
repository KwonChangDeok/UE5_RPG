// MonsterBase Ŭ������ ��ӹ޾� �������Ͱ� �����ϴ� ����� ������ Ŭ�����Դϴ�.

#pragma once

#include <Components/WidgetComponent.h>
#include "GameFramework/ProjectileMovementComponent.h"

#include "../Monster/MonsterBase.h"
#include "BossMonster.generated.h"

UCLASS()
class ASSASSIN_API ABossMonster : public AMonsterBase
{
	GENERATED_BODY()
public:
	ABossMonster();
	
protected:
	bool mWaitEnable;

	FTimerHandle WaitTimer;

	FTimerHandle SkillTimer;

	FTimerHandle InitTimer;

	bool mSkillEnable;

	// ���� ������ �� ������ ��� ����ȭ�� ����������, ���� Ȯ�强�� ����Ѵٸ� ����ġ ���� �� �ִٰ� �����մϴ�.
	bool mIsBerserk;

	float BossSkillCoolTime;
	float BossWaitTime;

protected:
	virtual void BeginPlay() override;

public:
	void SetWaitTime()
	{
		mWaitEnable = true;
	}

	void SetWaitEnd()
	{
		mWaitEnable = false;
	}

	bool GetWaitEnable()
	{
		return mWaitEnable;
	}

	void SetSkillEnable()
	{
		mSkillEnable = true;
	}

	void SetSkillDisEnable()
	{
		mSkillEnable = false;
	}

	bool GetSkillEnable()
	{
		return mSkillEnable;
	}

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	// ������ ��ų�� �ǰݽ�, �÷��̾ �˾� ���·� ����� ���� ������ �Լ��Դϴ�.
	// TakeDamage�� �����ϴ� ���� �� �� Ŭ���� �ڵ尡 �� ���̶�� �����մϴ�.
	void SkillDamage(float DamageAmount, class APlayerCharacter* DamagedPlayer);

	void InitializeInfo();
};
