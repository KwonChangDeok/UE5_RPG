
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

	// InProgress를 리턴하여 노드를 빠져나가지 못하도록
	return EBTNodeResult::InProgress;
}

void UTargetTrace::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// 실시간 형변환은 무거운 작업입니다. TickTask이를 수행한 것은 최적화에 굉장히 악영향을 끼쳤을것으로 생각됩니다.
	// 깊이 생각하지 않고 코드를 짠 결과인 것 같아 부끄럽습니다.
	// 차라리 블랙보드 변수로 관련 정보를 유지하고, 틱에선 유효성 검사만 수행하는 것이 올바르다고 생각합니다.
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	AMonsterBase* Monster = Cast<AMonsterBase>(Controller->GetPawn());
	ACharacter* Target = Cast<ACharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(_T("Target")));
	UMonsterAnimInstance* AnimInst = Monster->GetAnimInstance();

	// 종료조건 검사
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
