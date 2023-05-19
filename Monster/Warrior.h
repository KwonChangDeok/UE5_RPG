/*
 Monster 클래스를 상속받아 구현한 전사 몬스터입니다. 
 Sentinel과 같은 로직으로 구현하되 공격력, 방어력, 애니메이션 및 메쉬설정 등의 요소들이 데이터테이블을 통해 다른값으로 관리됩니다.
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
