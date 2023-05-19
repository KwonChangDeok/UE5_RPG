#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"
#include "AssassinCharacter.h"
#include "MyPlayerController.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	mMoveDir = 0.f;
	mSpeedRatio = 0.f;
	mIsFalling = false;
	mAttackEnable = true;
	mSkillEnable = true;
	mAttackIndex = 0;
	mUltimateEnable = true;
	mHitEnable = true;
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (!IsValid(PlayerCharacter))
	{
		return;
	}

	MoveComp = PlayerCharacter->GetCharacterMovement();
	mSpeedRatio = MoveComp->Velocity.Size() / MoveComp->MaxWalkSpeed;
	mIsFalling = MoveComp->IsFalling();
}

void UPlayerAnimInstance::Attack()
{
	if (!mAttackEnable)
	{
		return;
	}

	Montage_SetPosition(mAttackMontageArray[mAttackIndex], 0.f);
	Montage_Play(mAttackMontageArray[mAttackIndex]);
	MoveComp->MaxWalkSpeed = 0.f;

	mAttackIndex = (mAttackIndex + 1) % mAttackMontageArray.Num();
}

void UPlayerAnimInstance::Skill(int32 Case)
{
	if(!mSkillEnable)
	{
		return;
	}

	Montage_SetPosition(mSkillMontageArray[Case], 0.f);
	Montage_Play(mSkillMontageArray[Case]);
}

void UPlayerAnimInstance::Ultimate()
{
	if (!mUltimateEnable)
	{
		return;
	}

	Montage_SetPosition(mUltimateMontage, 0.f);
	Montage_Play(mUltimateMontage);
}

void UPlayerAnimInstance::Hit()
{
	if (mSkillEnable && mUltimateEnable && mHitEnable)
	{
		Montage_SetPosition(mHitMontage, 0.f);
		Montage_Play(mHitMontage);

		mHitEnable = false;
		mAttackEnable = false;
		GetWorld()->GetTimerManager().SetTimer(HitTimer, this, &UPlayerAnimInstance::SetHitEnable, 3.f, false, -1.f);
	}
}

void UPlayerAnimInstance::KnockDown()
{
	if (mUltimateEnable)
	{
		PlayerCharacter->Jump();

		Montage_SetPosition(mKnockDownMontage, 0.f);
		Montage_Play(mKnockDownMontage);

		mHitEnable = false;
		mAttackEnable = false;
		mSkillEnable = false;
		mUltimateEnable = false;
		mAttackIndex = 0;
	}
}

FVector UPlayerAnimInstance::GetDestDir()
{
	AMyPlayerController* Controller = Cast<AMyPlayerController>(PlayerCharacter->GetController());
	if (!IsValid(Controller))
	{
		return FVector::ZeroVector;
	}

	FHitResult	Result;

	bool Hit = Controller->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, false, Result);
	
	if (Hit)
	{
		FVector PlayerLoc = PlayerCharacter->GetActorLocation();
		PlayerLoc = PlayerLoc - FVector(0.f, 0.f, PlayerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		FVector DestLoc = Result.ImpactPoint;

		FVector Dir = DestLoc - PlayerLoc;

		Dir.Z = 0;
		Dir.Normalize();
		return Dir;
	}

	return FVector::ZeroVector;
}

void UPlayerAnimInstance::AnimNotify_RecoveryStart()
{
	MoveComp->MaxWalkSpeed = 0.f;
}

void UPlayerAnimInstance::AnimNotify_RecoveryEnd()
{
	MoveComp->MaxWalkSpeed = PlayerCharacter->GetPlayerInfo().MaxWalkSpeed;
}

void UPlayerAnimInstance::AnimNotify_AttackStart()
{
	if (GetDestDir() != FVector::ZeroVector)
	{
		FRotator Dir(0.f, GetDestDir().Rotation().Yaw, 0.f);
		PlayerCharacter->SetActorRotation(Dir);
	}

	mAttackEnable = false;
}

void UPlayerAnimInstance::AnimNotify_AttackEnable()
{
	mAttackEnable = true;
}

void UPlayerAnimInstance::AnimNotify_AttackEnd()
{
	mAttackIndex = 0;
	MoveComp->MaxWalkSpeed = PlayerCharacter->GetPlayerInfo().MaxWalkSpeed;
}

void UPlayerAnimInstance::AnimNotify_AttackSingle()
{
	PlayerCharacter->AttackSingle();
}

void UPlayerAnimInstance::AnimNotify_AttackSpinning()
{
	PlayerCharacter->AttackSpinning();
}

void UPlayerAnimInstance::AnimNotify_AttackTwin()
{
	PlayerCharacter->AttackTwin();
}

void UPlayerAnimInstance::AnimNotify_AttackFinish()
{
	PlayerCharacter->AttackFinish();
}

void UPlayerAnimInstance::AnimNotify_SkillStart()
{
	mAttackEnable = false;
	mSkillEnable = false;
}

void UPlayerAnimInstance::AnimNotify_SkillEnd()
{
	mAttackEnable = true;
	mSkillEnable = true;

	mAttackIndex = 0;
}

void UPlayerAnimInstance::AnimNotify_DashStart()
{
	PlayerCharacter->SetDash(true);
	MoveComp->MaxWalkSpeed = 2000.f;
}

void UPlayerAnimInstance::AnimNotify_DashEnd()
{
	PlayerCharacter->SetDash(false);

	PlayerCharacter->GetController()->StopMovement();
	MoveComp->MaxWalkSpeed = PlayerCharacter->GetPlayerInfo().MaxWalkSpeed;
}

void UPlayerAnimInstance::AnimNotify_HitEnd()
{
	mAttackEnable = true;
	MoveComp->MaxWalkSpeed = PlayerCharacter->GetPlayerInfo().MaxWalkSpeed;
}

void UPlayerAnimInstance::AnimNotify_KnockDownEnd()
{
	mHitEnable = true;
	mAttackEnable = true;
	mSkillEnable = true;
	mUltimateEnable = true;
}

void UPlayerAnimInstance::AnimNotify_Throw()
{
	PlayerCharacter->SkillZApply();
}

void UPlayerAnimInstance::AnimNotify_SkillZStart()
{
	if (GetDestDir() != FVector::ZeroVector)
	{
		FRotator Dir(0.f, GetDestDir().Rotation().Yaw, 0.f);
		PlayerCharacter->SetActorRotation(Dir);
	}
	MoveComp->MaxWalkSpeed = 0.f;
}

void UPlayerAnimInstance::AnimNotify_SkillZEnd()
{
	MoveComp->MaxWalkSpeed = PlayerCharacter->GetPlayerInfo().MaxWalkSpeed;
}

void UPlayerAnimInstance::AnimNotify_SkillZAttack()
{
	PlayerCharacter->SkillZFinish();
}

void UPlayerAnimInstance::AnimNotify_SkillXStart()
{
	if (GetDestDir() != FVector::ZeroVector)
	{
		FRotator Dir(0.f, GetDestDir().Rotation().Yaw, 0.f);
		PlayerCharacter->SetActorRotation(Dir);
	}
	MoveComp->MaxWalkSpeed = 0.f;
}

void UPlayerAnimInstance::AnimNotify_SkillXEnd()
{
	MoveComp->MaxWalkSpeed = PlayerCharacter->GetPlayerInfo().MaxWalkSpeed;
	PlayerCharacter->SetSkillXSecondEnable();
}

void UPlayerAnimInstance::AnimNotify_SkillXAttack()
{
	PlayerCharacter->SkillXApply();
}

void UPlayerAnimInstance::AnimNotify_SkillCStart()
{
	if (GetDestDir() != FVector::ZeroVector)
	{
		FRotator Dir(0.f, GetDestDir().Rotation().Yaw, 0.f);
		PlayerCharacter->SetActorRotation(Dir);
	}
	MoveComp->MaxWalkSpeed = 0.f;
}

void UPlayerAnimInstance::AnimNotify_SkillCEnd()
{
	MoveComp->MaxWalkSpeed = PlayerCharacter->GetPlayerInfo().MaxWalkSpeed;
}

void UPlayerAnimInstance::AnimNotify_SkillCAttack()
{
	PlayerCharacter->SkillCApply();
}

void UPlayerAnimInstance::AnimNotify_UltimateStart()
{
	if (GetDestDir() != FVector::ZeroVector)
	{
		FRotator Dir(0.f, GetDestDir().Rotation().Yaw, 0.f);
		PlayerCharacter->SetActorRotation(Dir);
	}

	mAttackEnable = false;
	mSkillEnable = false;
	mUltimateEnable = false;

	MoveComp->MaxWalkSpeed = 0.f;
}

void UPlayerAnimInstance::AnimNotify_UltimateEnd()
{
	mAttackEnable = true;
	mSkillEnable = true;
	mUltimateEnable = true;
	mAttackIndex = 0;

	MoveComp->MaxWalkSpeed = PlayerCharacter->GetPlayerInfo().MaxWalkSpeed;
	MoveComp->JumpZVelocity = 600.f;
}

void UPlayerAnimInstance::AnimNotify_UltimateTeleport()
{
	PlayerCharacter->SkillVTeleport();
}

void UPlayerAnimInstance::AnimNotify_UltimateAttack()
{
	PlayerCharacter->SkillVApply();
}

void UPlayerAnimInstance::AnimNotify_RightStep()
{
	PlayerCharacter->FootStep(false);
}

void UPlayerAnimInstance::AnimNotify_LeftStep()
{
	PlayerCharacter->FootStep(true);
}
