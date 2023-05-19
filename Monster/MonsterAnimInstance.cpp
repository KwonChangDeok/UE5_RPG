#include "MonsterAnimInstance.h"
#include "MonsterBase.h"
#include "../BossMonster/RockGiant.h"
#include "../BossMonster/Lich.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
	mAnimType = EMonsterAnimType::Idle;
	mAttackType = EMonsterAttackAnimType::Attack1;

	mKnockDown = false;
	mDeath = false;
	mSkillEnable = true;
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Monster = Cast<AMonsterBase>(TryGetPawnOwner());

	if (!IsValid(Monster))
	{
		return;
	}
	
	MoveComp = Monster->GetCharacterMovement();
}

void UMonsterAnimInstance::Hit()
{
	if (mKnockDown || mDeath)
	{
		return;
	}

	Montage_SetPosition(mHitMontage, 0.f);
	Montage_Play(mHitMontage);

	MoveComp->MaxWalkSpeed = 0.f;
}

void UMonsterAnimInstance::KnockDown()
{
	if (mKnockDown || mDeath || !mSkillEnable)
	{
		return;
	}

	Montage_SetPosition(mKnockDownMontage, 0.f);
	Montage_Play(mKnockDownMontage);
}

void UMonsterAnimInstance::Skill(int32 Case)
{
	if (mKnockDown || mDeath || !mSkillEnable)
	{
		return;
	}

	Montage_SetPosition(mSkillMontageArray[Case], 0.f);
	Montage_Play(mSkillMontageArray[Case]);
}

void UMonsterAnimInstance::Berserk()
{
	if (mKnockDown || mDeath || !mSkillEnable)
	{
		return;
	}

	Montage_SetPosition(mBerserkMontage, 0.f);
	Montage_Play(mBerserkMontage);
}

void UMonsterAnimInstance::AnimNotify_AttackEnd()
{
	MoveComp->MaxWalkSpeed = Monster->GetMonsterInfo().MaxWalkSpeed;
	Monster->SetAttackEnable(true);
	mAnimType = EMonsterAnimType::Idle;
}


void UMonsterAnimInstance::AnimNotify_Attack()
{
	Monster->Attack();
}

void UMonsterAnimInstance::AnimNotify_HitEnd()
{
	MoveComp->MaxWalkSpeed = Monster->GetMonsterInfo().MaxWalkSpeed;
	Monster->SetAttackEnable(true);
}

void UMonsterAnimInstance::AnimNotify_KnockDownStart()
{
	mKnockDown = true;
}

void UMonsterAnimInstance::AnimNotify_KnockDownEnd()
{
	mKnockDown = false;
	mSkillEnable = true;
	MoveComp->MaxWalkSpeed = Monster->GetMonsterInfo().MaxWalkSpeed;
	Monster->SetAttackEnable(true);
}

void UMonsterAnimInstance::AnimNotify_DeathStart()
{
	mDeath = true;
}

void UMonsterAnimInstance::AnimNotify_DeathEnd()
{
	Monster->Destroy();
}

void UMonsterAnimInstance::AnimNotify_BossDeath()
{
	ARockGiant* Giant = Cast<ARockGiant>(TryGetPawnOwner());

	if (!IsValid(Giant))
	{
		return;
	}

	Giant->PlayOutro();
}

void UMonsterAnimInstance::AnimNotify_BossSkillStart()
{
	mSkillEnable = false;
	MoveComp->MaxWalkSpeed = 0.f;
}

void UMonsterAnimInstance::AnimNotify_BossSkillEnd()
{
	mSkillEnable = true;
	MoveComp->MaxWalkSpeed = Monster->GetMonsterInfo().MaxWalkSpeed;
}

void UMonsterAnimInstance::AnimNotify_Skill1Attack()
{
	ARockGiant* Giant = Cast<ARockGiant>(TryGetPawnOwner());

	if (!IsValid(Giant))
	{
		return;
	}

	Giant->Skill1Attack();
}

void UMonsterAnimInstance::AnimNotify_Skill2Hand()
{
	ARockGiant* Giant = Cast<ARockGiant>(TryGetPawnOwner());

	if (!IsValid(Giant))
	{
		return;
	}

	Giant->Skill2Hand();
}

void UMonsterAnimInstance::AnimNotify_Skill2Attack()
{
	ARockGiant* Giant = Cast<ARockGiant>(TryGetPawnOwner());

	if (!IsValid(Giant))
	{
		return;
	}

	Giant->Skill2Attack();
}

void UMonsterAnimInstance::AnimNotify_ThrowRock()
{
	ARockGiant* Giant = Cast<ARockGiant>(TryGetPawnOwner());

	if (!IsValid(Giant))
	{
		return;
	}
	
	Giant->ThrowRock();
}

void UMonsterAnimInstance::AnimNotify_LichSkill1Attack()
{
	ALich* Lich = Cast<ALich>(TryGetPawnOwner());

	if (!IsValid(Lich))
	{
		return;
	}

	Lich->Skill1Attack();
}

void UMonsterAnimInstance::AnimNotify_LichSkill2Attack()
{
	ALich* Lich = Cast<ALich>(TryGetPawnOwner());

	if (!IsValid(Lich))
	{
		return;
	}

	Lich->Skill2Attack();
}

void UMonsterAnimInstance::AnimNotify_LichSkill3Attack()
{
	ALich* Lich = Cast<ALich>(TryGetPawnOwner());

	if (!IsValid(Lich))
	{
		return;
	}

	Lich->Skill3Attack();
}
