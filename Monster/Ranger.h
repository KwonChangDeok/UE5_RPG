/*
Monster Ŭ������ ��ӹ޾� ������ ���Ÿ� ���� �����Դϴ�. 
LineTraceMultiByChannel �Լ��� �̿��� ĳ���Ϳ��� �浹�� �˻��Ͽ� ���� ����, ���п��θ� �Ǵ��� �� �ֵ��� �����߽��ϴ�.
�̿��� �������� ���������̺��� ���� ���ϰ� ������ �� �ֵ��� �����߽��ϴ�.
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
