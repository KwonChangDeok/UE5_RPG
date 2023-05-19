// Fill out your copyright notice in the Description page of Project Settings.


#include "AssassinCharacter.h"
#include "PlayerSkillProjectile.h"
#include "../Monster/MonsterBase.h"
#include "./Skill/Shadow.h"
#include "NavigationSystem.h"

AAssassinCharacter::AAssassinCharacter()
{
	// �޽� ����
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AssassinAsset(_T("SkeletalMesh'/Game/AssassinGirl/Mesh/SK_AssassinGirl_HoodOff.SK_AssassinGirl_HoodOff'"));

	if (AssassinAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(AssassinAsset.Object);
		mShadowMesh = AssassinAsset.Object;
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	}

	// ���� �޽� ����
	static ConstructorHelpers::FObjectFinder<UStaticMesh> AssassinDagger(_T("StaticMesh'/Game/AssassinGirl/Mesh/SM_ASSASSINGIRL_DAGGER.SM_ASSASSINGIRL_DAGGER'"));

	if (AssassinDagger.Succeeded())
	{
		mWeapon_l = CreateDefaultSubobject<UStaticMeshComponent>(_T("Weapon_l"));
		mWeapon_l->SetStaticMesh(AssassinDagger.Object);
		mWeapon_l->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, _T("weapon_l_socket"));
		mWeapon_l->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		mWeapon_r = CreateDefaultSubobject<UStaticMeshComponent>(_T("Weapon_r"));
		mWeapon_r->SetStaticMesh(AssassinDagger.Object);
		mWeapon_r->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, _T("weapon_r_socket"));
		mWeapon_r->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	
	// �ִ�Ŭ���� ����
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimClass(_T("AnimBlueprint'/Game/Player/Animation/ABAssassin.ABAssassin_C'"));

	if (AnimClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);
	}

	mPlayerInfoRowName = _T("Assassin");
}

void AAssassinCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAssassinCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Attack���� �Լ����� ������ �ߺ��Ǵ� ������ �����ϴ�.
// �̸� ������ �Լ�ȭ�Ͽ� �ڵ��� �ߺ��� ���̰�, �������� ����Ű�� ���� ���ٰ� �����մϴ�.

// ���� �⺻���� ���ݷ°� ���� ����
void AAssassinCharacter::AttackSingle()
{
	FVector StartLoc = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	FVector EndLoc = StartLoc + GetActorForwardVector() * mPlayerInfo.AttackRange;

	FCollisionQueryParams param(NAME_None, false, this);
	TArray<FHitResult> Result;

	FQuat CapsuleRotation = FRotator(0.f, 90.f, 0.f).Quaternion();

	bool Collision = GetWorld()->SweepMultiByChannel(Result, StartLoc, EndLoc, CapsuleRotation,
		ECollisionChannel::ECC_GameTraceChannel6, FCollisionShape::MakeSphere(50.f), param);

	if (Collision)
	{
		int32 Count = Result.Num();

		for (int32 i = 0; i < Count; i++)
		{
			float Damage = mPlayerInfo.AttackPoint * FMath::FRandRange(0.8, 1.2);

			AMonsterBase* Monster = Cast<AMonsterBase>(Result[i].GetActor());
			if (IsValid(Monster))
			{
				Monster->SetCritical(false);

				// ũ��Ƽ�� ������
				if (FMath::RandRange(1, 100) <= mPlayerInfo.CriticalRate)
				{
					Damage *= mPlayerInfo.CriticalDamage;
					Monster->SetCritical(true);
				}

				Monster->TakeDamage(Damage, FDamageEvent(), GetController(), this);

				MakeParticle(Result[i].ImpactPoint);

				mPlayerInfo.SpecialPoint = (mPlayerInfo.SpecialPoint + 5) > 100 ? 100 : (mPlayerInfo.SpecialPoint + 5);
				mMainUI->SetSP(mPlayerInfo.SpecialPoint / 100.f);
			}
		}
	}
}

// ���ݷ��� �⺻������, ������ ����
void AAssassinCharacter::AttackSpinning()
{
	FVector StartLoc = GetActorLocation();
	FVector EndLoc = GetActorLocation();

	FCollisionQueryParams param(NAME_None, false, this);
	TArray<FHitResult> Result;

	bool Collision = GetWorld()->SweepMultiByChannel(Result, StartLoc, EndLoc, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel6, FCollisionShape::MakeSphere(mPlayerInfo.AttackRange), param);

	if (Collision)
	{
		int32 Count = Result.Num();

		for (int32 i = 0; i < Count; i++)
		{
			float Damage = mPlayerInfo.AttackPoint * FMath::FRandRange(0.8, 1.2);

			AMonsterBase* Monster = Cast<AMonsterBase>(Result[i].GetActor());
			if (IsValid(Monster))
			{
				Monster->SetCritical(false);

				// ũ��Ƽ�� ������
				if (FMath::RandRange(1, 100) <= mPlayerInfo.CriticalRate)
				{
					Damage *= mPlayerInfo.CriticalDamage;
					Monster->SetCritical(true);
				}

				Monster->TakeDamage(Damage, FDamageEvent(), GetController(), this);

				MakeParticle(Result[i].ImpactPoint);

				mPlayerInfo.SpecialPoint = (mPlayerInfo.SpecialPoint + 5) > 100 ? 100 : (mPlayerInfo.SpecialPoint + 5);
				mMainUI->SetSP(mPlayerInfo.SpecialPoint / 100.f);
			}
		}
	}
}

// ���ݷ��� 1.5�� ������ �⺻
void AAssassinCharacter::AttackTwin()
{
	FVector StartLoc = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	FVector EndLoc = StartLoc + GetActorForwardVector() * mPlayerInfo.AttackRange;

	FCollisionQueryParams param(NAME_None, false, this);
	TArray<FHitResult> Result;

	FQuat CapsuleRotation = FRotator(0.f, 90.f, 0.f).Quaternion();

	bool Collision = GetWorld()->SweepMultiByChannel(Result, StartLoc, EndLoc, CapsuleRotation,
		ECollisionChannel::ECC_GameTraceChannel6, FCollisionShape::MakeSphere(50.f), param);

	if (Collision)
	{
		int32 Count = Result.Num();

		for (int32 i = 0; i < Count; i++)
		{
			float Damage = mPlayerInfo.AttackPoint * FMath::FRandRange(0.8, 1.2) * 1.5f;

			AMonsterBase* Monster = Cast<AMonsterBase>(Result[i].GetActor());
			if (IsValid(Monster))
			{
				Monster->SetCritical(false);

				// ũ��Ƽ�� ������
				if (FMath::RandRange(1, 100) <= mPlayerInfo.CriticalRate)
				{
					Damage *= mPlayerInfo.CriticalDamage;
					Monster->SetCritical(true);
				}
			
				Monster->TakeDamage(Damage, FDamageEvent(), GetController(), this);

				MakeParticle(Result[i].ImpactPoint);

				mPlayerInfo.SpecialPoint = (mPlayerInfo.SpecialPoint + 5) > 100 ? 100 : (mPlayerInfo.SpecialPoint + 5);
				mMainUI->SetSP(mPlayerInfo.SpecialPoint / 100.f);
			}
		}
	}
}

// ���ݷ� 2�� ���� �⺻ ���������Ʈ 10����
void AAssassinCharacter::AttackFinish()
{
	FVector StartLoc = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	FVector EndLoc = StartLoc + GetActorForwardVector() * mPlayerInfo.AttackRange;

	FCollisionQueryParams param(NAME_None, false, this);
	TArray<FHitResult> Result;

	FQuat CapsuleRotation = FRotator(0.f, 90.f, 0.f).Quaternion();

	bool Collision = GetWorld()->SweepMultiByChannel(Result, StartLoc, EndLoc, CapsuleRotation,
		ECollisionChannel::ECC_GameTraceChannel6, FCollisionShape::MakeSphere(80.f), param);

	if (Collision)
	{
		int32 Count = Result.Num();

		for (int32 i = 0; i < Count; i++)
		{
			AMonsterBase* Monster = Cast<AMonsterBase>(Result[i].GetActor());

			float Damage = mPlayerInfo.AttackPoint * FMath::FRandRange(0.8, 1.2) * 2.f;
			if (IsValid(Monster))
			{
				Monster->SetCritical(false);

				// ũ��Ƽ�� ������
				if (FMath::RandRange(1, 100) <= mPlayerInfo.CriticalRate)
				{
					Damage *= mPlayerInfo.CriticalDamage;
					Monster->SetCritical(true);
				}

				Monster->TakeDamage(Damage, FDamageEvent(), GetController(), this);

				MakeParticle(Result[i].ImpactPoint);

				mPlayerInfo.SpecialPoint = (mPlayerInfo.SpecialPoint + 10) > 100 ? 100 : (mPlayerInfo.SpecialPoint + 10);
				mMainUI->SetSP(mPlayerInfo.SpecialPoint / 100.f);
			}
		}
	}
}

void AAssassinCharacter::SkillZApply()
{
	APlayerSkillProjectile* SkillProjectile = NewObject<APlayerSkillProjectile>(this, APlayerSkillProjectile::StaticClass());
	
	UStaticMesh* StaticMesh = LoadObject<UStaticMesh>(nullptr, _T("StaticMesh'/Game/AssassinGirl/Mesh/SM_ASSASSINGIRL_DAGGER.SM_ASSASSINGIRL_DAGGER'"));

	if (IsValid(StaticMesh) && IsValid(SkillProjectile))
	{
		SkillProjectile->SetStaticMesh(StaticMesh);
		SkillProjectile->SetSkillDamage(2.f);
		SkillProjectile->SetSkillRange(4000.f);
	}

	FActorSpawnParameters SpawnParam;
	SpawnParam.Template = SkillProjectile;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<APlayerSkillProjectile>(GetActorLocation() + GetActorForwardVector() * 100.f, GetActorRotation(), SpawnParam);
}

void AAssassinCharacter::SkillZFinish()
{
	FVector StartLoc = GetActorLocation();
	FVector EndLoc = GetActorLocation();

	FCollisionQueryParams param(NAME_None, false, this);
	TArray<FHitResult> Result;

	bool Collision = GetWorld()->SweepMultiByChannel(Result, StartLoc, EndLoc, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel6, FCollisionShape::MakeSphere(100.f), param);

	if (Collision)
	{
		int32 Count = Result.Num();

		for (int32 i = 0; i < Count; i++)
		{
			float Damage = mPlayerInfo.AttackPoint * FMath::FRandRange(0.8, 1.2) * 2.f;

			AMonsterBase* Monster = Cast<AMonsterBase>(Result[i].GetActor());
			if (IsValid(Monster))
			{
				Monster->SetCritical(false);

				// ũ��Ƽ�� ������
				if (FMath::RandRange(1, 100) <= mPlayerInfo.CriticalRate)
				{
					Damage *= mPlayerInfo.CriticalDamage;
					Monster->SetCritical(true);
				}

				Monster->TakeDamage(Damage, FDamageEvent(), GetController(), this);

				MakeParticle(Result[i].ImpactPoint);

				mPlayerInfo.SpecialPoint = (mPlayerInfo.SpecialPoint + 10) > 100 ? 100 : (mPlayerInfo.SpecialPoint + 10);
				mMainUI->SetSP(mPlayerInfo.SpecialPoint / 100.f);
			}
		}
	}
}

void AAssassinCharacter::SkillXApply()
{
	mSkillXComeBackLocation = GetActorLocation();

	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	mShadow = GetWorld()->SpawnActor<AShadow>(GetMesh()->GetComponentLocation(), GetMesh()->GetComponentRotation(), SpawnParam);
	mShadow->SetMesh(mShadowMesh);
	mShadow->CopyAnimation(GetMesh());

	FVector OrgLocation = GetActorLocation();
	
	OrgLength = 1200.f;
	mSpringArm->TargetArmLength = 1200.f;
	TargetArmKey = true;

	SetActorLocation(GetActorLocation() + GetActorForwardVector() * 600.f);

	FVector DestLocation = GetActorLocation() + GetActorForwardVector() * mPlayerInfo.AttackRange;

	FCollisionQueryParams param(NAME_None, false, this);
	TArray<FHitResult> Result;

	FQuat CapsuleRotation = FRotator(0.f, 90.f, 0.f).Quaternion();

	bool Collision = GetWorld()->SweepMultiByChannel(Result, OrgLocation, DestLocation, CapsuleRotation,
		ECollisionChannel::ECC_GameTraceChannel6, FCollisionShape::MakeSphere(150.f), param);

	if (Collision)
	{
		int32 Count = Result.Num();

		for (int32 i = 0; i < Count; i++)
		{
			float Damage = mPlayerInfo.AttackPoint * FMath::FRandRange(0.8, 1.2) * 3.f;

			AMonsterBase* Monster = Cast<AMonsterBase>(Result[i].GetActor());
			if (IsValid(Monster))
			{
				Monster->SetCritical(false);

				// ũ��Ƽ�� ������
				if (FMath::RandRange(1, 100) <= mPlayerInfo.CriticalRate)
				{
					Damage *= mPlayerInfo.CriticalDamage;
					Monster->SetCritical(true);
				}

				Monster->TakeDamage(Damage, FDamageEvent(), GetController(), this);

				MakeParticle(Result[i].ImpactPoint);

				mPlayerInfo.SpecialPoint = (mPlayerInfo.SpecialPoint + 20) > 100 ? 100 : (mPlayerInfo.SpecialPoint + 20);
				mMainUI->SetSP(mPlayerInfo.SpecialPoint / 100.f);
			}
		}
	}
}

void AAssassinCharacter::SkillCApply()
{
	FVector StartLoc = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	FVector EndLoc = StartLoc + GetActorForwardVector() * mPlayerInfo.AttackRange;

	FCollisionQueryParams param(NAME_None, false, this);
	TArray<FHitResult> Result;

	FQuat CapsuleRotation = FRotator(0.f, 90.f, 0.f).Quaternion();

	bool Collision = GetWorld()->SweepMultiByChannel(Result, StartLoc, EndLoc, CapsuleRotation,
		ECollisionChannel::ECC_GameTraceChannel6, FCollisionShape::MakeSphere(80.f), param);

	if (Collision)
	{
		int32 Count = Result.Num();

		for (int32 i = 0; i < Count; i++)
		{
			float Damage = mPlayerInfo.AttackPoint * FMath::FRandRange(0.8, 1.2) * 2.f;

			AMonsterBase* Monster = Cast<AMonsterBase>(Result[i].GetActor());
			if (IsValid(Monster))
			{
				Monster->SetCritical(false);

				// ũ��Ƽ�� ������
				if (FMath::RandRange(1, 100) <= mPlayerInfo.CriticalRate)
				{
					Damage *= mPlayerInfo.CriticalDamage;
					Monster->SetCritical(true);
				}

				Monster->TakeDamage(Damage, FDamageEvent(), GetController(), this);

				MakeParticle(Result[i].ImpactPoint);

				mPlayerInfo.SpecialPoint = (mPlayerInfo.SpecialPoint + 20) > 100 ? 100 : (mPlayerInfo.SpecialPoint + 20);
				mMainUI->SetSP(mPlayerInfo.SpecialPoint / 100.f);
			}
		}
	}
}

void AAssassinCharacter::SkillVTeleport()
{
	if (UltimateLocation != FVector::ZeroVector)
	{
		FVector TargetLoc = UltimateLocation;

		float Distance = FVector::Distance(TargetLoc, GetActorLocation());

		OrgLength = 600.f + Distance;

		mSpringArm->TargetArmLength = OrgLength;

		TargetArmKey = true;

		if (GetWorld()->FindTeleportSpot(this, TargetLoc, GetActorRotation()))
		{
			SetActorLocation(TargetLoc);
		}
		else
		{
			// �̵��� �� ���� ��ġ�� ���, �̵��� �� �ִ� ���� ����� ��ġ�� �̵�
			FVector NewLocation;
			if (UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, TargetLoc, NewLocation, 200.f))
			{
				SetActorLocation(NewLocation);
			}
		}
		UltimateLocation = FVector::ZeroVector;
	}
}

void AAssassinCharacter::SkillVApply()
{
	FVector StartLoc = GetActorLocation();
	FVector EndLoc = GetActorLocation();

	FCollisionQueryParams param(NAME_None, false, this);
	TArray<FHitResult> Result;

	bool Collision = GetWorld()->SweepMultiByChannel(Result, StartLoc, EndLoc, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel6, FCollisionShape::MakeSphere(500.f), param);

	if (Collision)
	{
		int32 Count = Result.Num();

		for (int32 i = 0; i < Count; i++)
		{
			float Damage = mPlayerInfo.AttackPoint * FMath::FRandRange(0.8, 1.2) * 10.f;

			AMonsterBase* Monster = Cast<AMonsterBase>(Result[i].GetActor());
			if (IsValid(Monster))
			{
				Monster->SetCritical(false);

				// ũ��Ƽ�� ������
				if (FMath::RandRange(1, 100) <= mPlayerInfo.CriticalRate + 50)
				{
					Damage *= mPlayerInfo.CriticalDamage;
					Monster->SetCritical(true);
				}

				Monster->SetIsUltimate(true);
				Monster->TakeDamage(Damage, FDamageEvent(), GetController(), this);
				MakeParticle(Result[i].ImpactPoint);
			}
		}
	}
}

void AAssassinCharacter::MakeParticle(FVector ImpactPoint)
{
	UParticleSystem* EffectAsset = LoadObject<UParticleSystem>(nullptr, _T("ParticleSystem'/Game/ParagonCountess/FX/Particles/Abilities/BlinkStrike/FX/P_Countess_BlinkStrike_HitFX.P_Countess_BlinkStrike_HitFX'"));

	if (IsValid(EffectAsset))
	{
		FRotator SpawnRotation = GetActorRotation();

		UParticleSystemComponent* ParticleSystemComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EffectAsset, ImpactPoint, SpawnRotation);

		ParticleSystemComponent->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));
		ParticleSystemComponent->bAutoDestroy = true;
	}
}
