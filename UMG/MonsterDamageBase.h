// UserWidget Ŭ������ ��ӹ޾� �������� ��Ÿ�� �ؽ�Ʈ ����� ����� ������ �����Ͽ�, 
// ���������� ũ��Ƽ�� ���θ� �ľ��� �� �ֵ��� �ϴ� Ŭ�����Դϴ�.

#pragma once

#include <Components\TextBlock.h>

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "MonsterDamageBase.generated.h"

UCLASS()
class ASSASSIN_API UMonsterDamageBase : public UUserWidget
{
	GENERATED_BODY()
private:
	UTextBlock* mDamage;
	float mPositionX;
	float mPositionY;

public:
	virtual void NativeConstruct() override;

public:
	void SetDamage(FText Damage);
	void SetCriticalDamage(FText Damage);
};
