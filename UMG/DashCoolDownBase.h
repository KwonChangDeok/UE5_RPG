// UserWidget Ŭ������ ��ӹ޾� �뽬 ��ų�� ��Ÿ�� ������ �ؽ�Ʈ�� �̹����� ���� ������ ǥ���� �� �ֵ��� �ϴ� Ŭ�����Դϴ�

#pragma once

#include <Components/ProgressBar.h>
#include <Components/Image.h>

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "DashCoolDownBase.generated.h"

UCLASS()
class ASSASSIN_API UDashCoolDownBase : public UUserWidget
{
	GENERATED_BODY()
private:
	UProgressBar* mDashBar;
	UImage* mDashBack;

public:
	virtual void NativeConstruct() override;

public:
	void SetDashBar(float Ratio);
};
