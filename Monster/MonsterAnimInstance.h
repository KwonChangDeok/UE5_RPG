// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

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
