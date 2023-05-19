/*
 Monster 클래스를 상속받아 구현한 정찰 몬스터입니다. 
 SweepMultiByChannel 함수를 이용해 캐릭터와의 충돌검사를 수행, 공격의 성공 여부를 판단할 수 있도록 구현했습니다. 
 이외의 정보들은 데이터테이블을 통해 관리되며 정찰병은 다른 몬스터보다 넓은 대플레이어 탐지범위를 갖는 특징을 갖도록 했습니다.
*/

#pragma once

#include "Monster.h"
#include "Sentinel.generated.h"

UCLASS()
class ASSASSIN_API ASentinel : public AMonster
{
	GENERATED_BODY()
public:
	ASentinel();

public:
	virtual void Attack() override;
};
