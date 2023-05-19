// MonsterBase 클래스를 상속받아 일반 몬스터들이 공유하는 기능을 구현한 클래스입니다.

#pragma once

#include <Components/WidgetComponent.h>
#include "GameFramework/ProjectileMovementComponent.h"

#include "MonsterBase.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

UCLASS()
class ASSASSIN_API AMonster : public AMonsterBase
{
	GENERATED_BODY()

public:
	AMonster();
	FTimerHandle InitTimer;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* AIController);

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

public:
	virtual void Attack();

	void InitializeInfo();
};
