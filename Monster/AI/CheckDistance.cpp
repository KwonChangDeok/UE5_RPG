// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckDistance.h"
#include "MonsterAIController.h"
#include "../MonsterBase.h"

UCheckDistance::UCheckDistance()
{
}

bool UCheckDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AMonsterAIController* Contoroller = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());
	if (!IsValid(Contoroller))
	{
		return false;
	}

	AMonsterBase* Monster = Cast<AMonsterBase>(Contoroller->GetPawn());
	if (!IsValid(Monster))
	{
		return false;
	}

	ACharacter* Target = Cast<ACharacter>(Contoroller->GetBlackboardComponent()->GetValueAsObject(_T("Target")));
	if (!IsValid(Target))
	{
		return false;
	}

	const FMonsterInfo& Info = Monster->GetMonsterInfo();

	FVector LocOfMonster = Monster->GetActorLocation() - FVector(0.f, 0.f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	FVector LocOfCharacter = Target->GetActorLocation() - FVector(0.f, 0.f, Target->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	float Distance = FVector::Distance(LocOfMonster, LocOfCharacter);

	Distance = Distance - Monster->GetCapsuleComponent()->GetScaledCapsuleRadius() - Target->GetCapsuleComponent()->GetScaledCapsuleRadius();

	float Threshold = 0.f;

	switch (mCheckType)
	{
	case ECheckDistanceType::Attack:
		Threshold = Info.AttackRange;
		break;
	case ECheckDistanceType::Trace:
		Threshold = Info.TraceDistance;
		break;
	}

	return Distance <= Threshold;
}