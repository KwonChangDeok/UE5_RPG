// Fill out your copyright notice in the Description page of Project Settings.


#include "Lich.h"
#include "../Monster/MonsterAnimInstance.h"
#include "../Monster/AI/MonsterAIController.h"
#include "../Player/PlayerCharacter.h"
#include "../AssassinGameModeBase.h"
#include "../Player/Skill/Decal.h"
#include "LichSkill3Object.h"
#include "../UMG/MonsterInfoBase.h"

ALich::ALich()
{
	mMonsterInfoRowName = _T("Lich");

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	GetCapsuleComponent()->SetWorldScale3D(FVector(2.f, 2.f, 2.f));

	BossSkillCoolTime = 10.f;
	BossWaitTime = 2.f;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(_T("SkeletalMesh'/Game/ParagonSevarog/Characters/Heroes/Sevarog/Skins/Tier_1_5/MaskedReaper/Mesh/Sevarog_MaskedReaper_GDC.Sevarog_MaskedReaper_GDC'"));

	if (MeshAsset.Succeeded())
	{
		BerserkMesh = MeshAsset.Object;
	}
}

void ALich::PossessedBy(AController* AIController)
{
	Super::PossessedBy(AIController);

	MonsterAIController->SetBehaviorTree(_T("BehaviorTree'/Game/Monster/AI/BTLich.BTLich'"));
	MonsterAIController->SetBlackboard(_T("BlackboardData'/Game/Monster/AI/BBLich.BBLich'"));
}

void ALich::Attack()
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
			if (mIsBerserk)
			{
				APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Result[i].GetActor());
				BerserkAttack(PlayerCharacter);
			}
			else
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
}

float ALich::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (mMonsterInfo.HP / (float)mMonsterInfo.HPMax < 0.5f && !mIsBerserk && mAnimInst->GetSkillEnable())
	{
		GetMesh()->SetVisibility(false);
		MonsterAIController->BrainComponent->StopLogic(_T("Berserk"));

		mBerserkSequence = LoadObject<ULevelSequence>(nullptr, _T("LevelSequence'/Game/LevelSequence/LichBerserkLevelSequence.LichBerserkLevelSequence'"));
		if (IsValid(mBerserkSequence))
		{
			mBerserkSetting.bHideHud = true;
			mBerserkSetting.bHidePlayer = true;
			mBerserkSetting.bDisableMovementInput = true;
			mBerserkSetting.bDisableLookAtInput = true;

			if (!mBerserkPlayer)
			{
				mBerserkPlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
					GetWorld(), mBerserkSequence, mBerserkSetting, mBerserkActor);
			}

			mBerserkPlayer->Play();

			mBerserkPlayer->OnFinished.AddDynamic(this, &ALich::BerserkFinish);
		}

		GetMesh()->SetSkeletalMesh(BerserkMesh);
	}

	if (mMonsterInfo.HP == 0 && mAnimInst->GetSkillEnable())
	{
		SetActorLocation(FVector(1084.f, -1780.f, 26.f));
		MonsterAIController->BrainComponent->StopLogic(_T("LichGimmick"));
		mAnimInst->SetMonsterAnim(EMonsterAnimType::LichGimmick);

		GetWorldTimerManager().SetTimer(ResurrectionTimer, this, &ALich::Resurrection, 30.f, false, -1.f);
	}

	return 0.f;
}

// 아래 공격 스킬들의 중복되는 코드를 함수화하는 것이 좋다고 생각합니다.

void ALich::Skill1Attack()
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

			if (IsValid(Player))
			{
				float HPRatio = Player->GetPlayerInfo().HP / (float)Player->GetPlayerInfo().HPMax;

				if (HPRatio >= 0.5f)
				{
					float HillAmount = HPRatio - 0.5f;

					mMonsterInfo.HP += mMonsterInfo.HPMax * HillAmount;
					if (mMonsterInfo.HP > mMonsterInfo.HPMax)
					{
						mMonsterInfo.HP = mMonsterInfo.HPMax;
					}

					UMonsterInfoBase* mMonsterInfoBase = Cast<UMonsterInfoBase>(mWidgetComponent->GetWidget());
					mMonsterInfoBase->SetHP(mMonsterInfo.HP / (float)mMonsterInfo.HPMax);
					FString temp = FString::FromInt((mMonsterInfo.HP / (float)mMonsterInfo.HPMax) * 100) + FString(_T("%"));
					mMonsterInfoBase->SetText(FText::FromString(temp));

					Player->GetPlayerInfo().HP = Player->GetPlayerInfo().HPMax * 0.5;

					AAssassinGameModeBase* GameMode = Cast<AAssassinGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
					GameMode->GetMainUI()->SetHP(Player->GetPlayerInfo().HP, Player->GetPlayerInfo().HPMax);

					Player->GetAnimInst()->KnockDown();
				}
			}
		}
	}
}

void ALich::Skill2Attack()
{
	FVector StartLoc = GetActorLocation();
	FVector EndLoc = GetActorLocation();

	FCollisionQueryParams param(NAME_None, false, this);
	TArray<FHitResult> Result;

	bool Collision = GetWorld()->SweepMultiByChannel(Result, StartLoc, EndLoc, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel7, FCollisionShape::MakeSphere(5000.f), param);

	if (Collision)
	{
		int32 Count = Result.Num();

		for (int32 i = 0; i < Count; i++)
		{
			APlayerCharacter* Player = Cast<APlayerCharacter>(Result[i].GetActor());

			if (IsValid(Player))
			{
				if (Player->GetActorLocation().Z < 120.f)
				{
					SkillDamage(300.f, Player);
				}
			}
		}
	}
}

void ALich::Skill3Attack()
{
	FVector StartLoc = GetActorLocation();
	FVector EndLoc = GetActorLocation();

	FCollisionQueryParams param(NAME_None, false, this);
	TArray<FHitResult> Result;

	bool Collision = GetWorld()->SweepMultiByChannel(Result, StartLoc, EndLoc, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel7, FCollisionShape::MakeSphere(5000.f), param);

	if (Collision)
	{
		int32 Count = Result.Num();

		for (int32 i = 0; i < Count; i++)
		{
			APlayerCharacter* Player = Cast<APlayerCharacter>(Result[i].GetActor());

			if (IsValid(Player))
			{
				int32 RandVal = FMath::RandRange(-800, 800);

				FVector TargetLoc = Player->GetActorLocation();

				TargetLoc.X += RandVal;

				RandVal = FMath::RandRange(-800, 800);

				TargetLoc.Y += RandVal;

				TargetLoc.Z = 0.f;
				
				FActorSpawnParameters SpawnParam;

				ADecal* Decal = GetWorld()->SpawnActor<ADecal>(SpawnParam);
				Decal->SetDecalWorldLocation(TargetLoc);
				Decal->SetActorScale3D(FVector(1.f, 0.3f, 0.3f));
				Decal->SetLifeSpan(0.5f);
				
				UParticleSystem* ParticleSystem = LoadObject<UParticleSystem>(nullptr, _T("ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/Ultimate/FX/P_UltActivate.P_UltActivate'"));
				UParticleSystemComponent* ParticleSystemComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, TargetLoc, FRotator::ZeroRotator);

				ALichSkill3Object* LichSkill3Object = NewObject<ALichSkill3Object>(this, ALichSkill3Object::StaticClass());

				FActorSpawnParameters ObjectParam;
				ObjectParam.Template = LichSkill3Object;
				ObjectParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				GetWorld()->SpawnActor<ALichSkill3Object>(TargetLoc, FRotator::ZeroRotator, ObjectParam);
			}
		}
	}
}

void ALich::BerserkAttack(APlayerCharacter* Target)
{
	if (!IsValid(Target))
	{
		return;
	}

	if (Target->GetPlayerInfo().HP == 1)
	{
		Target->TakeDamage(1.f, FDamageEvent(), GetController(), this);
	}

	int32 Damage = Target->GetPlayerInfo().HP * 0.9;

	Target->GetPlayerInfo().HP -= Damage;
	
	AAssassinGameModeBase* GameMode = Cast<AAssassinGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->GetMainUI()->SetHP(Target->GetPlayerInfo().HP, Target->GetPlayerInfo().HPMax);

	Target->GetAnimInst()->KnockDown();
}

void ALich::Resurrection()
{
	MonsterAIController->BrainComponent->RestartLogic();
	mMonsterInfo.HP = mMonsterInfo.HPMax * 0.5;

	UMonsterInfoBase* mMonsterInfoBase = Cast<UMonsterInfoBase>(mWidgetComponent->GetWidget());
	mMonsterInfoBase->SetHP(mMonsterInfo.HP / (float)mMonsterInfo.HPMax);
	FString temp = FString::FromInt((mMonsterInfo.HP / (float)mMonsterInfo.HPMax) * 100) + FString(_T("%"));
	mMonsterInfoBase->SetText(FText::FromString(temp));

	mAnimInst->SetMonsterAnim(EMonsterAnimType::Idle);
	mAnimInst->SetSkillEnable(true);
}

void ALich::Outro()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->AddGold(mMonsterInfo.Gold);
	}

	Destroy();

	mDeathSequence = LoadObject<ULevelSequence>(nullptr, _T("LevelSequence'/Game/LevelSequence/LichOutroLevelSequence.LichOutroLevelSequence'"));
	if (IsValid(mDeathSequence))
	{
		mDeathSetting.bHideHud = true;
		mDeathSetting.bHidePlayer = true;
		mDeathSetting.bDisableMovementInput = true;
		mDeathSetting.bDisableLookAtInput = true;

		if (!mDeathPlayer)
		{
			mDeathPlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
				GetWorld(), mDeathSequence, mDeathSetting, mDeathActor);
		}

		mDeathPlayer->Play();
	}
}

void ALich::BerserkFinish()
{
	GetMesh()->SetVisibility(true);
	MonsterAIController->BrainComponent->RestartLogic();
	mAnimInst->SetSkillEnable(true);
	mIsBerserk = true;
}
