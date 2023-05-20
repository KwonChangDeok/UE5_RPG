// MonsterBase 클래스를 상속받아 보스몬스터가 공유하는 기능을 구현한 클래스입니다.

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

	// 현재 구현한 두 보스는 모두 광폭화가 존재하지만, 추후 확장성을 고려한다면 적절치 않을 수 있다고 생각합니다.
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

	// 보스의 스킬에 피격시, 플레이어를 넉업 상태로 만들기 위해 구현한 함수입니다.
	// TakeDamage로 통합하는 편이 좀 더 클린한 코드가 될 것이라고 생각합니다.
	void SkillDamage(float DamageAmount, class APlayerCharacter* DamagedPlayer);

	void InitializeInfo();
};
