/*
Actor Ŭ������ ��ӹ޾� ���忡 ��ġ�� �������� ���͸� ���� �� �������ϰ�, Ư�� �������� ��Ʈ�� �� �ֵ��� �ϴ� ����� ������ Ŭ�����Դϴ�.
������ �󿡼� ��ȯ�� ���Ϳ� ����������, ���� �������� ������ �� �ֵ��� �����߽��ϴ�.
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

	// ���漱���� Ȱ���� ��� ��ȯ���� ����
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
