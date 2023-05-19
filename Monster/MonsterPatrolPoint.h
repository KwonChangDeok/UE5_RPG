// Actor 클래스를 상속받아 월드에 배치해 좌표값을 가질 수 있도록 구현한 클래스입니다.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "MonsterPatrolPoint.generated.h"

UCLASS()
class ASSASSIN_API AMonsterPatrolPoint : public AActor
{
	GENERATED_BODY()
	
public:
	AMonsterPatrolPoint();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	USceneComponent* mRoot;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
