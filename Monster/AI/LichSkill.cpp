// Fill out your copyright notice in the Description page of Project Settings.


#include "LichSkill.h"
#include "MonsterAIController.h"
#include "../../BossMonster/Lich.h"
#include "../MonsterAnimInstance.h"
#include "../../Player/Skill/Decal.h"

ULichSkill::ULichSkill()
{
	NodeName = _T("LichSkill");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
	IsBerserk = false;
}

EBTNodeResult::Type ULichSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	Boss = Cast<ALich>(Controller->GetPawn());
	Target = Cast<ACharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(_T("Target")));
	UMonsterAnimInstance* AnimInst = Boss->GetAnimInstance();

	if (!IsValid(Controller) || !IsValid(Boss) || !IsValid(Target) || !IsValid(AnimInst))
	{
		return EBTNodeResult::Failed;
	}

	if (!IsBerserk)
	{
		SkillNum = FMath::RandRange(1, 3);
	}
	else
	{
		SkillNum = FMath::RandRange(1, 4);
	}

	if (Boss->GetMonsterInfo().HP / (float)Boss->GetMonsterInfo().HPMax < 0.5f)
	{
		IsBerserk = true;
	}

	FVector	MonsterLoc = Boss->GetActorLocation();
	FVector	TargetLoc = Target->GetActorLocation();

	MonsterLoc = MonsterLoc - FVector(0.f, 0.f, Boss->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	TargetLoc = TargetLoc - FVector(0.f, 0.f, Target->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	FVector	Dir = TargetLoc - MonsterLoc;

	Dir.Z = 0.f;
	Dir.Normalize();

	Boss->SetActorRotation(FRotator(0.f, Dir.Rotation().Yaw, 0.f));

	RandTime = FMath::RandRange(3, 6);

	FActorSpawnParameters SpawnParam;

	switch (SkillNum)
	{
	case 1:
		AnimInst->Skill(0);

		AccDelta = 0.f;
		GetWorld()->GetTimerManager().SetTimer(Skill1Fade, this, &ULichSkill::Fade, 0.05f, true, -1.f);
		GetWorld()->GetTimerManager().SetTimer(Skill1Timer, this, &ULichSkill::Skill1Teleport, (float)RandTime, false, -1.f);

		Skill1Key = false;
		break;

	case 2:
		AnimInst->Skill(2);

		AnimInst->SetSkillEnable(false);

		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		Decal = GetWorld()->SpawnActor<ADecal>(SpawnParam);
		Decal->SetDecalWorldLocation(FVector(0.f, 0.f, 0.f));
		Decal->SetActorScale3D(FVector(1.f, 20.f, 20.f));
		break;

	case 3:
		AnimInst->Skill(3);
		AnimInst->SetSkillEnable(false);
		break;

	case 4:
		AnimInst->Skill(4);
		Skill4Key = true;
		AnimInst->SetSkillEnable(false);
		break;
	}

	return EBTNodeResult::InProgress;
}

void ULichSkill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// 틱에서의 실행시간 형변환 문제
	// 보스몬스터의 경우 월드상에 하나의 객체만 배치될 것이기 때문에, 멤버변수로 유지하는 것이 적절하다고 생각합니다.
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	UMonsterAnimInstance* AnimInst = Boss->GetAnimInstance();

	FVector	MonsterLoc = Boss->GetActorLocation();
	FVector	TargetLoc = Target->GetActorLocation();

	MonsterLoc = MonsterLoc - FVector(0.f, 0.f, Boss->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	TargetLoc = TargetLoc - FVector(0.f, 0.f, Target->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	FVector	Dir = TargetLoc - MonsterLoc;

	Dir.Z = 0.f;
	Dir.Normalize();

	if (!IsValid(Controller) || !IsValid(Boss) || !IsValid(Target) || !IsValid(AnimInst))
	{
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);;
	}

	switch (SkillNum)
	{
	case 1:
		if (Skill1Key && AnimInst->GetSkillEnable())
		{
			return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
		break;

	case 2:
		if (AnimInst->GetSkillEnable())
		{
			Decal->Destroy();
			return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
		break;

	case 3:
		if (AnimInst->GetSkillEnable())
		{
			return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
		break;
	case 4:
		Boss->SetActorRotation(FRotator(0.f, Dir.Rotation().Yaw, 0.f));

		if (Skill4Key)
		{
			Skill4Move(DeltaSeconds);
		}

		if (AnimInst->GetSkillEnable())
		{
			return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
		break;
	}
}

void ULichSkill::Fade()
{
	Boss->SetActorLocation(Boss->GetActorLocation() - Boss->GetActorForwardVector() * 0.05f * 300.f);

	AccDelta += 0.05f;

	if (AccDelta > 2.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(Skill1Fade);
		UMeshComponent* MeshComponent = Boss->GetMesh();
		MeshComponent->SetVisibility(false);
	}
}

void ULichSkill::Skill1Teleport()
{
	UMonsterAnimInstance* AnimInst = Boss->GetAnimInstance();
	if (!IsValid(Boss) || !IsValid(Target) || !IsValid(AnimInst))
	{
		return;
	}

	UMeshComponent* MeshComponent = Boss->GetMesh();
	MeshComponent->SetVisibility(true);

	FVector	MonsterLoc = Boss->GetActorLocation();
	FVector	TargetLoc = Target->GetActorLocation();

	MonsterLoc = MonsterLoc - FVector(0.f, 0.f, Boss->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	TargetLoc = TargetLoc - FVector(0.f, 0.f, Target->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	FVector	Dir = TargetLoc - MonsterLoc;

	Dir.Z = 0.f;
	Dir.Normalize();

	FVector DestLoc = Target->GetActorLocation() + Dir * Target->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

	Boss->SetActorLocation(DestLoc);
	Boss->AddActorLocalRotation(FRotator(0.f, 180.f, 0.f));

	AnimInst->Skill(1);
	AnimInst->SetSkillEnable(false);
	Skill1Key = true;
}

void ULichSkill::Skill4Move(float DeltaTime)
{
	if (FVector::Distance(Boss->GetActorLocation(), Target->GetActorLocation()) < 400.f)
	{
		Skill4Key = false;
		return;
	}

	float InterpSpeed = 3.f;

	FVector NewLoc = FMath::VInterpTo(Boss->GetActorLocation(), Target->GetActorLocation(), DeltaTime, InterpSpeed);
	
	Boss->SetActorLocation(NewLoc);
}
