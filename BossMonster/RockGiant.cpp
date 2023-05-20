#include "RockGiant.h"
#include "../Player/PlayerCharacter.h"
#include "BossSkillPojectile.h"
#include "../Monster/MonsterAnimInstance.h"
#include "../Monster/AI/MonsterAIController.h"

ARockGiant::ARockGiant()
{
	mMonsterInfoRowName = _T("RockGiant");

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	GetCapsuleComponent()->SetWorldScale3D(FVector(2.f, 2.f, 2.f));

	mSequencePlayer = nullptr;
	mSequenceActor = nullptr;
}

void ARockGiant::PossessedBy(AController* AIController)
{
	Super::PossessedBy(AIController);

	MonsterAIController->SetBehaviorTree(_T("BehaviorTree'/Game/Monster/AI/BTGiant.BTGiant'"));
	MonsterAIController->SetBlackboard(_T("BlackboardData'/Game/Monster/AI/BBGiant.BBGiant'"));
}

// 아래 함수들에서 중복되는 충돌판정을 함수화 하는 것이 좋다고 생각합니다.

void ARockGiant::Attack()
{
	FVector StartLoc = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	FVector EndLoc = StartLoc + GetActorForwardVector() * mMonsterInfo.AttackRange;

	FCollisionQueryParams param(NAME_None, false, this);
	TArray<FHitResult> Result;

	FQuat CapsuleRotation = FRotator(0.f, 90.f, 0.f).Quaternion();

	bool Collision = GetWorld()->SweepMultiByChannel(Result, StartLoc, EndLoc, CapsuleRotation,
		ECollisionChannel::ECC_GameTraceChannel7, FCollisionShape::MakeSphere(50.f), param);

	if (Collision)
	{
		int32 Count = Result.Num();

		for (int32 i = 0; i < Count; i++)
		{
			float Damage = mMonsterInfo.AttackPoint * FMath::FRandRange(0.8, 1.2);

			APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Result[i].GetActor());
			if (IsValid(PlayerCharacter))
			{
				PlayerCharacter->TakeDamage(Damage, FDamageEvent(), GetController(), this);
			}
		}
	}
}

void ARockGiant::Skill1Attack()
{
	FVector StartLoc = GetActorLocation();
	FVector EndLoc = GetActorLocation();

	FCollisionQueryParams param(NAME_None, false, this);
	TArray<FHitResult> Result;

	bool Collision = GetWorld()->SweepMultiByChannel(Result, StartLoc, EndLoc, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel7, FCollisionShape::MakeSphere(500.f), param);

	if (Collision)
	{
		int32 Count = Result.Num();

		for (int32 i = 0; i < Count; i++)
		{
			APlayerCharacter* Player = Cast<APlayerCharacter>(Result[i].GetActor());

			float DamageAmount = 300.f;

			if (IsValid(Player))
			{
				SkillDamage(DamageAmount, Player);
			}
		}
	}
}

void ARockGiant::Skill2Hand()
{
	FVector StartLoc = GetActorLocation();
	FVector EndLoc = GetActorLocation();

	FCollisionQueryParams param(NAME_None, false, this);
	TArray<FHitResult> Result;

	bool Collision = GetWorld()->SweepMultiByChannel(Result, StartLoc, EndLoc, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel7, FCollisionShape::MakeSphere(200.f), param);

	if (Collision)
	{
		int32 Count = Result.Num();

		for (int32 i = 0; i < Count; i++)
		{
			APlayerCharacter* Player = Cast<APlayerCharacter>(Result[i].GetActor());

			float DamageAmount = 100.f;

			if (IsValid(Player))
			{
				SkillDamage(DamageAmount, Player);
			}
		}
	}
}

void ARockGiant::Skill2Attack()
{
	FVector StartLoc = GetActorLocation();
	FVector EndLoc = GetActorLocation();

	FCollisionQueryParams param(NAME_None, false, this);
	TArray<FHitResult> Result;

	bool Collision = GetWorld()->SweepMultiByChannel(Result, StartLoc, EndLoc, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel7, FCollisionShape::MakeSphere(1000.f), param);

	if (Collision)
	{
		int32 Count = Result.Num();

		for (int32 i = 0; i < Count; i++)
		{
			APlayerCharacter* Player = Cast<APlayerCharacter>(Result[i].GetActor());

			float DamageAmount = 300.f;

			if (IsValid(Player))
			{
				SkillDamage(DamageAmount, Player);
			}
		}
	}
}

void ARockGiant::ThrowRock()
{
	ABossSkillPojectile* SkillProjectile = NewObject<ABossSkillPojectile>(this, ABossSkillPojectile::StaticClass());

	UStaticMesh* StaticMesh = LoadObject<UStaticMesh>(nullptr, _T("StaticMesh'/Game/EnvironmentPack2/Meshes/Props/SM_Rock_01.SM_Rock_01'"));

	if (IsValid(StaticMesh) && IsValid(SkillProjectile))
	{
		SkillProjectile->SetStaticMesh(StaticMesh);
	}

	FActorSpawnParameters SpawnParam;
	SpawnParam.Template = SkillProjectile;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnLoc = GetActorLocation() + GetActorForwardVector() * 200.f;
	SpawnLoc.Z += 200.f;

	int32 RandRot = FMath::RandRange(-15, 15);

	FRotator SpawnRot = FRotator(GetActorRotation().Pitch + RandRot, GetActorRotation().Yaw + RandRot*2, GetActorRotation().Roll + RandRot);

	GetWorld()->SpawnActor<ABossSkillPojectile>(SpawnLoc, SpawnRot, SpawnParam);
}

float ARockGiant::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (mMonsterInfo.HP / (float)mMonsterInfo.HPMax < 0.5f && !mIsBerserk)
	{
		mIsBerserk = true;

		mMonsterInfo.ArmorPoint *= 0.5f;
		mMonsterInfo.AttackPoint *= 1.5f;
	}

	if (mMonsterInfo.HP == 0)
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(DamageCauser);
		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->AddGold(mMonsterInfo.Gold);
		}
		mAnimInst->SetMonsterAnim(EMonsterAnimType::Death);
	}
	return 0.0f;
}

void ARockGiant::PlayOutro()
{
	mLevelSequence = LoadObject<ULevelSequence>(nullptr, _T("LevelSequence'/Game/LevelSequence/RockGiantOutroLevelSequence.RockGiantOutroLevelSequence'"));
	if (IsValid(mLevelSequence))
	{
		mSetting.bHideHud = true;
		mSetting.bHidePlayer = true;
		mSetting.bDisableMovementInput = true;
		mSetting.bDisableLookAtInput = true;



		if (!mSequencePlayer)
		{
			mSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
				GetWorld(), mLevelSequence, mSetting, mSequenceActor);
		}

		mSequencePlayer->Play();
	}

	Destroy();
}
