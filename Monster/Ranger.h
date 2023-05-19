/*
Monster 클래스를 상속받아 구현한 원거리 공격 몬스터입니다. 
LineTraceMultiByChannel 함수를 이용해 캐릭터와의 충돌을 검사하여 공격 성공, 실패여부를 판단할 수 있도록 구현했습니다.
이외의 정보들은 데이터테이블을 통해 편리하게 편집할 수 있도록 구현했습니다.
*/

#pragma once

#include "Monster.h"
#include "Ranger.generated.h"

UCLASS()
class ASSASSIN_API ARanger : public AMonster
{
	GENERATED_BODY()
public:
	ARanger();

public:
	virtual void Attack() override;
	
};
