
#include "Attack.h"
#include "MonsterAIController.h"
#include "../MonsterBase.h"
#include "../MonsterAnimInstance.h"

UAttack::UAttack()
{
	NodeName = _T("Attack");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	FVector	MonsterLoc = Monster->GetActorLocation();
	FVector	TargetLoc = Target->GetActorLocation();

	MonsterLoc = MonsterLoc - FVector(0.f, 0.f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	TargetLoc = TargetLoc - FVector(0.f, 0.f, Target->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	FVector	Dir = TargetLoc - MonsterLoc;

	Dir.Z = 0.f;
	Dir.Normalize(); 

	Monster->SetActorRotation(FRotator(0.f, Dir.Rotation().Yaw, 0.f));

	AnimInst->SetRandomMonsterAttackType();
	AnimInst->SetMonsterAnim(EMonsterAnimType::Attack);
	Monster->SetAttackEnable(false);

	return EBTNodeResult::InProgress;
}

void UAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// TargetTrace 에서와 같이 무거운 형변환을 TickTask에서 수행한것은 잘못된 부분입니다.
	// 블랙보드 변수로 유지하고 틱에선 유효성 검사만 수행하는것이 성능에 좋다고 생각합니다.
	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	AMonsterBase* Monster = Cast<AMonsterBase>(Controller->GetPawn());
	ACharacter* Target = Cast<ACharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(_T("Target")));
	UMonsterAnimInstance* AnimInst = Monster->GetAnimInstance();

	Controller->StopMovement();

	if (!IsValid(Controller) || !IsValid(Monster) || !IsValid(Target))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	if (Monster->GetAttackEnable())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
}
