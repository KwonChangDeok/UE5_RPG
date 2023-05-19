// MonsterBase Ŭ������ ��ӹ޾� �Ϲ� ���͵��� �����ϴ� ����� ������ Ŭ�����Դϴ�.

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
