// UserWidget Ŭ������ ��ӹ޾� Z, X, C, V ��ų�� ��Ÿ�� ������ �ؽ�Ʈ�� �̹����� ���� ������ ǥ���� �� �ֵ��� �ϴ� Ŭ�����Դϴ�.

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
