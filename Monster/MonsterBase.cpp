#include "MonsterBase.h"
#include "../AssassinGameInstance.h"
#include "MonsterAnimInstance.h"
#include "AI/MonsterAIController.h"
#include "../UMG/MonsterInfoBase.h"
#include "../UMG/DamageActor.h"
#include "../Player/PlayerCharacter.h"
#include "../AssassinGameModeBase.h"

AMonsterBase::AMonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// AI 설정
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AMonsterAIController::StaticClass();

	// 콜리전 채널 설정
	GetCapsuleComponent()->SetCollisionProfileName(_T("Monster"));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	mPatrolEnable = true;
	mPatrolIndex = 0;

	mIsUltimate = false;
	mPatrolWaitTime = 0.f;

	mAttackEnable = true;
	mIsCritical = false;
}

void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();

	UAssassinGameInstance* GameInstance = GetWorld()->GetGameInstance<UAssassinGameInstance>();

	const FMonsterTableInfo* Info = GameInstance->GetMonsterTable(mMonsterInfoRowName);

	if (Info)
	{
		mMonsterInfo.Name = Info->Name;
		mMonsterInfo.AttackPoint = Info->AttackPoint;
		mMonsterInfo.ArmorPoint = Info->ArmorPoint;
		mMonsterInfo.HP = Info->HP;
		mMonsterInfo.HPMax = Info->HPMax;
		mMonsterInfo.Level = Info->Level;
		mMonsterInfo.Exp = Info->Exp;
		mMonsterInfo.Gold = Info->Gold;
		mMonsterInfo.MaxWalkSpeed = Info->MaxWalkSpeed;
		mMonsterInfo.AttackRange = Info->AttackRange;
		mMonsterInfo.TraceDistance = Info->TraceDistance;

		GetMesh()->SetSkeletalMesh(Info->Mesh);
		GetMesh()->SetAnimInstanceClass(Info->MonsterAnimClass);

		GetCharacterMovement()->MaxWalkSpeed = mMonsterInfo.MaxWalkSpeed;
	}

	mAnimInst = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
}

void AMonsterBase::PossessedBy(AController* AIController)
{
	Super::PossessedBy(AIController);

	MonsterAIController = Cast<AMonsterAIController>(AIController);
	if (!IsValid(MonsterAIController))
	{
		return;
	}

	if (!mBoss)
	{
		MonsterAIController->SetBehaviorTree(_T("BehaviorTree'/Game/Monster/AI/BTMonster.BTMonster'"));
		MonsterAIController->SetBlackboard(_T("BlackboardData'/Game/Monster/AI/BBMonster.BBMonster'"));
	}
}

void AMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AMonsterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	float Damage = (DamageAmount - mMonsterInfo.ArmorPoint) > 1.f ? (DamageAmount - mMonsterInfo.ArmorPoint) : 1.f;

	UMonsterInfoBase* mMonsterInfoBase = Cast<UMonsterInfoBase>(mWidgetComponent->GetWidget());

	mMonsterInfo.HP -= (int32)Damage;

	if (mMonsterInfo.HP < 0)
	{
		mMonsterInfo.HP = 0;
	}

	mMonsterInfoBase->SetHP(mMonsterInfo.HP / (float)mMonsterInfo.HPMax);
	FString temp = FString::FromInt((mMonsterInfo.HP / (float)mMonsterInfo.HPMax) * 100) + FString(_T("%"));
	mMonsterInfoBase->SetText(FText::FromString(temp));

	// SP가 80 이상일때, 5% 피흡
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(DamageCauser);
	if (IsValid(PlayerCharacter))
	{
		if (PlayerCharacter->GetPlayerInfo().SpecialPoint >= 80)
		{
			PlayerCharacter->GetPlayerInfo().HP =
				PlayerCharacter->GetPlayerInfo().HP + int32(Damage * 0.2) > PlayerCharacter->GetPlayerInfo().HPMax ?
				PlayerCharacter->GetPlayerInfo().HPMax : PlayerCharacter->GetPlayerInfo().HP + int32(Damage * 0.2);

			AAssassinGameModeBase* GameMode = Cast<AAssassinGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			GameMode->GetMainUI()->SetHP(PlayerCharacter->GetPlayerInfo().HP, PlayerCharacter->GetPlayerInfo().HPMax);
		}
	}

	FActorSpawnParameters SpawnParam;
	SpawnParam.Template = NewObject<ADamageActor>(this, ADamageActor::StaticClass());
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ADamageActor* DamageActor = GetWorld()->SpawnActor<ADamageActor>
		(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z), FRotator::ZeroRotator, SpawnParam);

	if (IsValid(DamageActor))
	{
		if (mIsCritical)
		{
			DamageActor->SetCriticalDamage(FText::AsNumber((int32)Damage));
		}
		else
		{
			DamageActor->SetDamage(FText::AsNumber((int32)Damage));
		}

		DamageActor->SetLifeSpan(2.f);
	}


	if (mMonsterInfo.HP == 0 && !mBoss)
	{
		mAnimInst->SetMonsterAnim(EMonsterAnimType::Death);

		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->AddGold(mMonsterInfo.Gold);
		}

		if (IsValid(MonsterAIController))
		{
			MonsterAIController->BrainComponent->StopLogic(_T("Death"));
			GetMovementComponent()->StopMovementImmediately();
		}
		return 0.f;
	}

	if (mIsUltimate)
	{
		GetCharacterMovement()->JumpZVelocity = 600.f;
		Jump();
		mAnimInst->KnockDown();
		mIsUltimate = false;
	}
	else if (!mBoss)
	{
		mAnimInst->Hit();
	}

	USoundWave* Sound = LoadObject<USoundWave>(nullptr, _T("SoundWave'/Game/Collections/MonsterHitSound.MonsterHitSound'"));

	if (IsValid(Sound))
	{
		UGameplayStatics::PlaySound2D(this, Sound);
	}

	// 최종적으로 사용하는 클래스이므로 아무값이나 반환.
	return 0.f;
}

void AMonsterBase::Attack()
{
}
