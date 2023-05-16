// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMonsterAIController();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UBehaviorTree* mBehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UBlackboardData* mBlackboardData;

protected:
	virtual void OnPossess(APawn* aPawn) override;

public:
	void SetBehaviorTree(const FString& Path);
	void SetBlackboard(const FString& Path);
};
