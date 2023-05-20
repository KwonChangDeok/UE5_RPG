// UserWidget 클래스를 상속받아 Z, X, C, V 스킬의 쿨타임 정보를 텍스트와 이미지의 색을 설정해 표현할 수 있도록 하는 클래스입니다.

#pragma once

#include <Components\ProgressBar.h>
#include <Components\TextBlock.h>
#include <Components/Image.h>

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "SkillCoolDownBase.generated.h"

UCLASS()
class ASSASSIN_API USkillCoolDownBase : public UUserWidget
{
	GENERATED_BODY()
private:
	UProgressBar* mSkillZBar;
	UProgressBar* mSkillXBar;
	UProgressBar* mSkillCBar;
	UProgressBar* mSkillVBar;

	UTextBlock* mSkillZText;
	UTextBlock* mSkillXText;

	UImage* mSkillZBack;
	UImage* mSkillXBack;
	UImage* mSkillCBack;
	UImage* mSkillVBack;

public:
	virtual void NativeConstruct() override;

public:
	void SetSkillZBar(float Ratio);
	void SetSkillXBar(float Ratio);
	void SetSkillCBar(float Ratio);
	void SetSkillVBar(float Ratio);

	void SetSkillZText(bool Enable);
	void SetSkillXText(bool Enable);

	void SetSkillVBack(FLinearColor Color);
};
