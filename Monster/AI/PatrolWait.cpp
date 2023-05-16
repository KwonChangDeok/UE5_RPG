// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolWait.h"
#include "MonsterAIController.h"
#include "../MonsterBase.h"
#include "../MonsterAnimInstance.h"

UPatrolWait::UPatrolWait()
{
	NodeName = _T("PatrolWait");
	bNotifyTick = true;
	bNotifyTaskFinished = true; 

	PatrolWaitTime = 2.f;
}

EBTNodeResult::Type UPatrolWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	AMonsterBase* Monster = Cast<AMonsterBase>(Controller->GetPawn());
	UMonsterAnimInstance* AnimInst = Monster->GetAnimInstance();

	if (!IsValid(Controller) || !IsValid(Monster) || !IsValid(AnimInst))
	{
		return EBTNodeResult::Failed;
	}

	if (Monster->GetPatrolEnable())
	{
		return EBTNodeResult::Failed;
	}

	Monster->GetCharacterMovement()->StopMovementImmediately();
	Monster->ClearPatrolWaitTime();
	AnimInst->SetMonsterAnim(EMonsterAnimType::Idle);

	return EBTNodeResult::InProgress;
}

void UPatrolWait::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	AMonsterBase* Monster = Cast<AMonsterBase>(Controller->GetPawn());
	UMonsterAnimInstance* AnimInst = Monster->GetAnimInstance();

	if (!IsValid(Controller) || !IsValid(Monster))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	Controller->StopMovement();


	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(_T("Target")));

	if (IsValid(Target))
	{
		Monster->SetPatrolEnable(false);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	Monster->AddPatrolWaitTime(DeltaSeconds);

	if (Monster->GetPatrolWaitTime() >= PatrolWaitTime)
	{
		Monster->SetPatrolEnable(true);
		Monster->ClearPatrolWaitTime();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
