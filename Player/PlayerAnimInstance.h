/*
AnimInstanc 클래스를 상속받아 애니메이션 블루프린트와 함께 작동하여 캐릭터의 애니메이션 시스템을 구성하는 클래스입니다. 
C++클래스에서 설정한 변수값을 이용해 적절한 애니메이션을 애니메이션블루프린트에서 재생하도록 구현하였으며
블루프린트에서 발생시키는 AnimNotify 이벤트를 처리해주는 역할을 수행합니다.
*/

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

UCLASS()
class ASSASSIN_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPlayerAnimInstance();

protected:
	// 블루프린트에 변수들을 공개하여 변수값에 따른 적절한 애니메이션을 재생할 수 있도록 구현했습니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float mMoveDir;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float mSpeedRatio;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool mIsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<UAnimMontage*>	mAttackMontageArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<UAnimMontage*>	mSkillMontageArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UAnimMontage*	mUltimateMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UAnimMontage* mHitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UAnimMontage* mKnockDownMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 mAttackIndex;

	bool mAttackEnable;

	bool mSkillEnable;

	bool mUltimateEnable;

	bool mHitEnable;

	FTimerHandle HitTimer;
	 
protected:
	class APlayerCharacter* PlayerCharacter;
	class UCharacterMovementComponent* MoveComp;

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	void SetMoveDir(float MoveDir)
	{
		mMoveDir = MoveDir;
	}

	float GetMoveDir()
	{
		return mMoveDir;
	}

	bool GetSkillEnable()
	{
		return mSkillEnable;
	}

	bool PlayerMoveEnable()
	{
		return mSkillEnable && mUltimateEnable && mAttackEnable;
	}

	void Attack();

	void Skill(int32 Case);

	void Ultimate();

	void Hit();

	void KnockDown();

	FVector GetDestDir();

	void SetHitEnable()
	{
		mHitEnable = true;
	}

	// AnimNotify 이벤트 처리함수들입니다.
public:
	UFUNCTION()
	void AnimNotify_RecoveryStart();

	UFUNCTION()
	void AnimNotify_RecoveryEnd();

	UFUNCTION()
	void AnimNotify_AttackStart();

	UFUNCTION()
	void AnimNotify_AttackEnable();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_AttackSingle();

	UFUNCTION()
	void AnimNotify_AttackSpinning();

	UFUNCTION()
	void AnimNotify_AttackTwin();

	UFUNCTION()
	void AnimNotify_AttackFinish();

	UFUNCTION()
	void AnimNotify_SkillStart();

	UFUNCTION()
	void AnimNotify_SkillEnd();

	UFUNCTION()
	void AnimNotify_DashStart();

	UFUNCTION()
	void AnimNotify_DashEnd();

	UFUNCTION()
	void AnimNotify_HitEnd();

	UFUNCTION()
	void AnimNotify_KnockDownEnd();

	UFUNCTION()
	void AnimNotify_Throw();

	UFUNCTION()
	void AnimNotify_SkillZStart();

	UFUNCTION()
	void AnimNotify_SkillZEnd();

	UFUNCTION()
	void AnimNotify_SkillZAttack();

	UFUNCTION()
	void AnimNotify_SkillXStart();

	UFUNCTION()
	void AnimNotify_SkillXEnd();

	UFUNCTION()
	void AnimNotify_SkillXAttack();

	UFUNCTION()
	void AnimNotify_SkillCStart();

	UFUNCTION()
	void AnimNotify_SkillCEnd();

	UFUNCTION()
	void AnimNotify_SkillCAttack();

	UFUNCTION()
	void AnimNotify_UltimateStart();

	UFUNCTION()
	void AnimNotify_UltimateEnd();

	UFUNCTION()
	void AnimNotify_UltimateTeleport();

	UFUNCTION()
	void AnimNotify_UltimateAttack();

	UFUNCTION()
	void AnimNotify_RightStep();

	UFUNCTION()
	void AnimNotify_LeftStep();
};
