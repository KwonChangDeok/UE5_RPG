
#include "TargetTrace.h"
#include "MonsterAIController.h"
#include "../MonsterBase.h"
#include "../MonsterAnimInstance.h"

UTargetTrace::UTargetTrace()
{
	NodeName = _T("TargetTrace");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UTargetTrace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	AMonsterBase* Monster = Cast<AMonsterBase>(Controller->GetPawn());
	ACharacter* Target = Cast<ACharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(_T("Target")));
	UMonsterAnimInstance* AnimInst = Monster->GetAnimInstance();

	if (!IsValid(Controller) || !IsValid(Monster) || !IsValid(Target) || !IsValid(AnimInst))
	{
		return EBTNodeResult::Failed;
	}

	Monster->GetCharacterMovement()->MaxWalkSpeed = Monster->GetMonsterInfo().MaxWalkSpeed;

	AnimInst->SetMonsterAnim(EMonsterAnimType::CombatRun);

	Monster->SetAttackEnable(true);

	UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);

	// InProgress�� �����Ͽ� ��带 ���������� ���ϵ���
	return EBTNodeResult::InProgress;
}

void UTargetTrace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// �ǽð� ����ȯ�� ���ſ� �۾��Դϴ�. TickTask�̸� ������ ���� ����ȭ�� ������ �ǿ����� ������������ �����˴ϴ�.
	// ���� �������� �ʰ� �ڵ带 § ����� �� ���� �β������ϴ�.
	// ���� ������ ������ ���� ������ �����ϰ�, ƽ���� ��ȿ�� �˻縸 �����ϴ� ���� �ùٸ��ٰ� �����մϴ�.
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	AMonsterBase* Monster = Cast<AMonsterBase>(Controller->GetPawn());
	ACharacter* Target = Cast<ACharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(_T("Target")));
	UMonsterAnimInstance* AnimInst = Monster->GetAnimInstance();

	// �������� �˻�
	if (IsValid(Controller) && IsValid(Monster) && IsValid(Target))
	{
		FVector LocOfMonster = Monster->GetActorLocation() - FVector(0.f, 0.f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		FVector LocOfCharacter = Target->GetActorLocation() - FVector(0.f, 0.f, Target->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

		float Distance = FVector::Distance(LocOfMonster, LocOfCharacter);

		Distance = Distance - Monster->GetCapsuleComponent()->GetScaledCapsuleRadius() - Target->GetCapsuleComponent()->GetScaledCapsuleRadius();

		if (Distance <= Monster->GetMonsterInfo().AttackRange)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		else if (Distance >= Monster->GetMonsterInfo().TraceDistance)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
}
