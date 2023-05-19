// Fill out your copyright notice in the Description page of Project Settings.

#include "BossWait.h"
#include "MonsterAIController.h"
#include "../../BossMonster/BossMonster.h"
#include "../MonsterAnimInstance.h"

UBossWait::UBossWait()
{
	NodeName = _T("BossWait");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBossWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	ABossMonster* Boss = Cast<ABossMonster>(Controller->GetPawn());

	UMonsterAnimInstance* AnimInst = Boss->GetAnimInstance();

	if (!IsValid(Controller) || !IsValid(Boss) || !IsValid(AnimInst))
	{
		return EBTNodeResult::Failed;
	}

	if (!Boss->GetWaitEnable())
	{
		return EBTNodeResult::Failed;
	}

	AnimInst->SetMonsterAnim(EMonsterAnimType::Idle);

	WaitTime = 0.f;

	return EBTNodeResult::InProgress;
}

void UBossWait::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// 실행시간 형변환 문제
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	ABossMonster* Boss = Cast<ABossMonster>(Controller->GetPawn());
	UMonsterAnimInstance* AnimInst = Boss->GetAnimInstance();

	if (!IsValid(Controller) || !IsValid(Boss))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	Controller->StopMovement();

	WaitTime += DeltaSeconds;

	if (WaitTime > FMath::RandRange(1, 5))
	{
		Boss->SetWaitEnd();
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
}
