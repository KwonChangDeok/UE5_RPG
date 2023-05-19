// Fill out your copyright notice in the Description page of Project Settings.


#include "Patrol.h"
#include "MonsterAIController.h"
#include "../MonsterBase.h"
#include "../MonsterAnimInstance.h"

UPatrol::UPatrol()
{
	NodeName = _T("Patrol");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	AMonsterBase* Monster = Cast<AMonsterBase>(Controller->GetPawn());
	UMonsterAnimInstance* AnimInst = Monster->GetAnimInstance();

	if (!IsValid(Controller) || !IsValid(Monster) || !IsValid(AnimInst))
	{
		return EBTNodeResult::Failed;
	}

	if (!Monster->GetPatrolEnable())
	{
		return EBTNodeResult::Failed;
	}

	if (Monster->GetPatrolLocation() == FVector::ZeroVector)
	{
		Monster->GetCharacterMovement()->StopMovementImmediately();
		AnimInst->SetMonsterAnim(EMonsterAnimType::Idle);
		return EBTNodeResult::Failed;
	}

	FVector	MonsterLoc = Monster->GetActorLocation();
	FVector	TargetLoc = Monster->GetPatrolLocation();

	MonsterLoc = MonsterLoc - FVector(0.f, 0.f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	FVector	Dir = TargetLoc - MonsterLoc;

	Dir.Z = 0.f;
	Dir.Normalize();

	Monster->SetActorRotation(FRotator(0.f, Dir.Rotation().Yaw, 0.f));

	Monster->GetCharacterMovement()->MaxWalkSpeed = Monster->GetMonsterInfo().MaxWalkSpeed * 0.7f;
	AnimInst->SetMonsterAnim(EMonsterAnimType::Run);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, TargetLoc);

	return EBTNodeResult::InProgress;
}

void UPatrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// 공통적으로 제가 실수한 Tick에서의 실행시간 형변환 문제입니다.
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	AMonsterBase* Monster = Cast<AMonsterBase>(Controller->GetPawn());
	UMonsterAnimInstance* AnimInst = Monster->GetAnimInstance();

	if (!IsValid(Controller) || !IsValid(Monster))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (IsValid(Target))
	{
		Monster->SetPatrolEnable(false);

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	FVector	MonsterLoc = Monster->GetActorLocation();
	FVector	TargetLoc = Monster->GetPatrolLocation();

	MonsterLoc.Z = TargetLoc.Z;

	float Distance = FVector::Distance(MonsterLoc, TargetLoc);

	if (Distance < Monster->GetCapsuleComponent()->GetScaledCapsuleRadius() + 30.f)
	{
		Controller->StopMovement();
		AnimInst->SetMonsterAnim(EMonsterAnimType::Idle);
		Monster->AddPatrolIndex();
		Monster->GetCharacterMovement()->MaxWalkSpeed = Monster->GetMonsterInfo().MaxWalkSpeed;
		Monster->SetPatrolEnable(false);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
