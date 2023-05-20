// UserWidget 클래스를 상속받아 대쉬 스킬의 쿨타임 정보를 텍스트와 이미지의 색을 설정해 표현할 수 있도록 하는 클래스입니다

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
