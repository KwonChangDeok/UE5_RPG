/*
 Monster Ŭ������ ��ӹ޾� ������ ���� �����Դϴ�. 
 SweepMultiByChannel �Լ��� �̿��� ĳ���Ϳ��� �浹�˻縦 ����, ������ ���� ���θ� �Ǵ��� �� �ֵ��� �����߽��ϴ�. 
 �̿��� �������� ���������̺��� ���� �����Ǹ� �������� �ٸ� ���ͺ��� ���� ���÷��̾� Ž�������� ���� Ư¡�� ������ �߽��ϴ�.
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
