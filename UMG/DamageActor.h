/*
Actor 클래스를 상속받아 각각의 객체가 데미지 위젯 하나를 표현하도록 설정한 클래스입니다. 
다수의 데미지 발생을 처리하기 위해 엑터를 활용했으며, 데미지는 발생 후 Z축 방향으로 상승하다 소멸합니다.
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
