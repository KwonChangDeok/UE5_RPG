/*
Actor Ŭ������ ��ӹ޾� ������ ��ü�� ������ ���� �ϳ��� ǥ���ϵ��� ������ Ŭ�����Դϴ�. 
�ټ��� ������ �߻��� ó���ϱ� ���� ���͸� Ȱ��������, �������� �߻� �� Z�� �������� ����ϴ� �Ҹ��մϴ�.
*/

#pragma once

#include <Components/WidgetComponent.h>

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "DamageActor.generated.h"

UCLASS()
class ASSASSIN_API ADamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADamageActor();

private:
	TSubclassOf<class UMonsterDamageBase> mMonsterDamageBaseClass;
	UWidgetComponent* mWidgetComponent;

	float CurZ;
	bool key;

	FTimerHandle InitTimer;

	FText mDamage;
	bool IsCritical;

	class UMonsterDamageBase* mMonsterDamageBase;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void SetDamage(FText Damage);
	void SetCriticalDamage(FText Damage);
	void SetDamagePosition(float DeltaTime);

	void MakeInstance();
};
