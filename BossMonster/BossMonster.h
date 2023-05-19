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


	void SkillDamage(float DamageAmount, class APlayerCharacter* DamagedPlayer);

	void InitializeInfo();
};
