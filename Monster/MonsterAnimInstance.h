/*
AnimInstanc 클래스를 상속받아 애니메이션 블루프린트와 함께 작동하여 몬스터의 애니메이션 시스템을 구성하는 클래스입니다.
C++클래스에서 설정한 변수값을 이용해 적절한 애니메이션을 애니메이션블루프린트에서 재생하도록 구현하였으며 
블루프린트에서 발생시키는 AnimNotify 이벤트를 처리해주는 역할을 수행합니다.
*/

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

// 보스몬스터와 일반 몬스터가 같은 애님인스턴스를 사용하는 것은 바람직하지 않다고 생각합니다.
// 역시 클래스 설계의 미숙함으로 인해 생긴 문제였습니다. 아무리 파생 블루프린트를 다르게 사용한다 하더라도,
// 이러한 설계는 코드의 유지보수성을 떨어뜨리고 확장에 불리하며 메모리를 낭비하게됩니다.

UENUM(BlueprintType)
enum class EMonsterAnimType : uint8
{
	Idle,
	Run,
	CombatRun,
	Attack,
	Death,
	LichGimmick
};

// 애니메이션에 랜덤성을 부여해 단조롭지 않게 느껴지도록 노력했습니다.
UENUM(BlueprintType)
enum class EMonsterAttackAnimType : uint8
{
	Attack1,
	Attack2,
	Attack3,
	Attack4,
	Attack5
};

UENUM(BlueprintType)
enum class EMonsterIdleAnimType : uint8
{
	Idle1,
	Idle2,
	Idle3,
};

/**
 * 
 */
UCLASS()
class ASSASSIN_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UMonsterAnimInstance();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	EMonsterAnimType mAnimType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	EMonsterAttackAnimType mAttackType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	EMonsterIdleAnimType mIdleType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UAnimMontage* mHitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UAnimMontage* mKnockDownMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<UAnimMontage*> mSkillMontageArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UAnimMontage* mBerserkMontage;

private:
	class AMonsterBase* Monster;
	class UCharacterMovementComponent* MoveComp;

	bool mKnockDown;
	bool mDeath;
	bool mSkillEnable;

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	void SetMonsterAnim(EMonsterAnimType Anim)
	{
		mAnimType = Anim;
	}

	void SetRandomMonsterAttackType()
	{
		mAttackType = (EMonsterAttackAnimType)FMath::RandRange(0, 4);
	}

	void SetRandomMonsterIdleType()
	{
		mIdleType = (EMonsterIdleAnimType)FMath::RandRange(0, 2);
	}

	bool GetSkillEnable()
	{
		return mSkillEnable;
	}

	void SetSkillEnable(bool Value)
	{
		mSkillEnable = Value;
	}

	void Hit();

	void KnockDown();

	void Skill(int32 Case);

	void Berserk();

public:
	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_HitEnd();

	UFUNCTION()
	void AnimNotify_KnockDownStart();

	UFUNCTION()
	void AnimNotify_KnockDownEnd();

	UFUNCTION()
	void AnimNotify_DeathStart();

	UFUNCTION()
	void AnimNotify_DeathEnd();

	UFUNCTION()
	void AnimNotify_BossDeath();

	UFUNCTION()
	void AnimNotify_BossSkillStart();

	UFUNCTION()
	void AnimNotify_BossSkillEnd();

	UFUNCTION()
	void AnimNotify_Skill1Attack();

	UFUNCTION()
	void AnimNotify_Skill2Hand();

	UFUNCTION()
	void AnimNotify_Skill2Attack();

	UFUNCTION()
	void AnimNotify_ThrowRock();

	UFUNCTION()
	void AnimNotify_LichSkill1Attack();

	UFUNCTION()
	void AnimNotify_LichSkill2Attack();

	UFUNCTION()
	void AnimNotify_LichSkill3Attack();
};
