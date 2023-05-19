/*
Actor 클래스를 상속받아 월드에 배치된 지점에서 몬스터를 생성 및 리스폰하고, 특정 지점들을 패트롤 수 있도록 하는 기능을 구현한 클래스입니다.
에디터 상에서 소환할 몬스터와 리스폰간격, 정찰 지점들을 설정할 수 있도록 구현했습니다.
*/

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawnPoint.generated.h"

UCLASS()
class ASSASSIN_API AMonsterSpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	AMonsterSpawnPoint();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	USceneComponent* mRoot;

	// 전방선언을 활용한 헤더 순환참조 방지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<class AMonster>	mSpawnMonsterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<class AMonsterPatrolPoint*> mMonsterPatrolPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float mMonsterRespawnTime;

private:
	class AMonsterBase* SpawnMonster;

	float mAccDelta;

	TArray<FVector> mMonsterPatolPointLocation;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	TArray<class AMonsterPatrolPoint*> GetPatrolPoint()
	{
		return mMonsterPatrolPoint;
	}
};
