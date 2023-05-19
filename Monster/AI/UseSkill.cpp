// Fill out your copyright notice in the Description page of Project Settings.


#include "UseSkill.h"
#include "MonsterAIController.h"
#include "../../BossMonster/RockGiant.h"
#include "../MonsterAnimInstance.h"
#include "../../Player/Skill/Decal.h"

UUseSkill::UUseSkill()
{
	NodeName = _T("UseSkill");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
	IsBerserk = false;
}

EBTNodeResult::Type UUseSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	key = false;

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	Boss = Cast<ARockGiant>(Controller->GetPawn());
	ACharacter* Target = Cast<ACharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(_T("Target")));
	UMonsterAnimInstance* AnimInst = Boss->GetAnimInstance();

	if (!IsValid(Controller) || !IsValid(Boss) || !IsValid(Target) || !IsValid(AnimInst))
	{
		return EBTNodeResult::Failed;
	}

	FVector	MonsterLoc = Boss->GetActorLocation();
	FVector	TargetLoc = Target->GetActorLocation();

	MonsterLoc = MonsterLoc - FVector(0.f, 0.f, Boss->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	TargetLoc = TargetLoc - FVector(0.f, 0.f, Target->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	float Distance = FVector::Distance(MonsterLoc, TargetLoc);

	if (Distance > 800.f)
	{
		SkillNum = 1;
	}
	else
	{
		SkillNum = 2;
	}

	if ((Boss->GetMonsterInfo().HP / (float)Boss->GetMonsterInfo().HPMax < 0.5f) && !IsBerserk)
	{
		SkillNum = 3;
	}

	FVector	Dir = TargetLoc - MonsterLoc;

	Dir.Z = 0.f;
	Dir.Normalize();

	Boss->SetActorRotation(FRotator(0.f, Dir.Rotation().Yaw, 0.f));


	FActorSpawnParameters SpawnParam;
	FVector SpawnLoc = Boss->GetActorLocation();

	switch (SkillNum)
	{
	case 1:
		if (Boss->GetCharacterMovement()->IsMovingOnGround())
		{
			LaunchVelocity = Dir * Distance;

			UCharacterMovementComponent* MoveComp = Boss->GetCharacterMovement();

			// 바위거인이 캐릭터를 향해 점프하도록 하는 스킬입니다.
			// 런치함수에 캐릭터와 바위거인 사이의 거리에 비례한 적절한 힘을 설정하면 원하는 결과를 얻을 수 있을 것이라 생각했습니다.
			// 비록 상수값을 실험적으로 테스트하며 값을 찾았지만, 원하는 바를 이룰 수 있었고, 추후 런치함수의 구체적인 동작을 이해하면
			// 보다 정확한 구현에 도움이 될 것이라 느꼈습니다. 그래서 현재는 엔진단에서 이해를 하고자 다이렉트X를 공부하고 있습니다.
			MoveComp->JumpZVelocity = 500.f;
			Boss->Jump();
			AnimInst->Skill(0);
			GetWorld()->GetTimerManager().SetTimer(LaunchTimer, this, &UUseSkill::Launch, 0.01f, false, -1.f);

			SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			Decal = GetWorld()->SpawnActor<ADecal>(SpawnParam);
			Decal->SetDecalWorldLocation(TargetLoc);
		}
		break;

	case 2:
		SpawnLoc.Z = 0.f;

		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AnimInst->Skill(2);

		Decal = GetWorld()->SpawnActor<ADecal>(SpawnParam);
		Decal->SetActorScale3D(FVector(3.f, 3.f, 3.f));
		Decal->SetDecalWorldLocation(SpawnLoc);

		AnimInst->SetSkillEnable(false);
		break;
	case 3:
		IsBerserk = true;

		AnimInst->Berserk();

		AnimInst->SetSkillEnable(false);
		break;
	}

	return EBTNodeResult::InProgress;
}

void UUseSkill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	// 틱함수에서의 실행시간 형변환 문제
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	ACharacter* Target = Cast<ACharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(_T("Target")));
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
		if (Boss->GetCharacterMovement()->IsMovingOnGround() && key)
		{
			AnimInst->Skill(1);
			Decal->Destroy();
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
		Boss->SetActorRotation(FRotator(0.f, Dir.Rotation().Yaw, 0.f));
		Boss->GetCharacterMovement()->MaxWalkSpeed = 0.f;
		if (AnimInst->GetSkillEnable())
		{
			return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
		break;
	}
}

void UUseSkill::Launch()
{
	Boss->LaunchCharacter(LaunchVelocity, true, false);
	key = true;
}
