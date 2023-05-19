
#include "TargetDetect.h"
#include "MonsterAIController.h"
#include "../MonsterBase.h"

UTargetDetect::UTargetDetect()
{
	NodeName = _T("TargetDetect");
}

void UTargetDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* Controller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(Controller))
	{
		return;
	}

	AMonsterBase* Monster = Cast<AMonsterBase>(Controller->GetPawn());

	if (!IsValid(Monster))
	{
		return;
	}

	const FMonsterInfo& Info = Monster->GetMonsterInfo();

	TArray<FOverlapResult> ResultArr;

	bool IsDetect = GetWorld()->OverlapMultiByChannel(ResultArr, Monster->GetActorLocation(), FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4, FCollisionShape::MakeSphere(Info.TraceDistance));

	if (IsDetect)
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(_T("Target"), ResultArr[0].GetActor());
	}
	else
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(_T("Target"), nullptr);
	}
}
