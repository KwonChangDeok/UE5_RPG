// Actor Ŭ������ ��ӹ޾� ���忡 ��ġ�� ��ǥ���� ���� �� �ֵ��� ������ Ŭ�����Դϴ�.

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
