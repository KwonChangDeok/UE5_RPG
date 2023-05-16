// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"

AMonsterAIController::AMonsterAIController()
{
}

void AMonsterAIController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (IsValid(mBehaviorTree) && IsValid(mBlackboardData))
	{
		UBlackboardComponent* BlackboardComp = Blackboard;
		if (UseBlackboard(mBlackboardData, BlackboardComp))
		{
			RunBehaviorTree(mBehaviorTree);
		}
	}
}

void AMonsterAIController::SetBehaviorTree(const FString& Path)
{
	mBehaviorTree = LoadObject<UBehaviorTree>(nullptr, *Path);
}

void AMonsterAIController::SetBlackboard(const FString& Path)
{
	mBlackboardData = LoadObject<UBlackboardData>(nullptr, *Path);
}
