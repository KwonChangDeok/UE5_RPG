/*
 Monster Ŭ������ ��ӹ޾� ������ ���� �����Դϴ�. 
 Sentinel�� ���� �������� �����ϵ� ���ݷ�, ����, �ִϸ��̼� �� �޽����� ���� ��ҵ��� ���������̺��� ���� �ٸ������� �����˴ϴ�.
*/
#pragma once

#include "Monster.h"
#include "Warrior.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API AWarrior : public AMonster
{
	GENERATED_BODY()
public:
	AWarrior();

public:
	virtual void Attack() override;
};
