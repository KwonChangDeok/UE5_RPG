// UserWidget Ŭ������ ��ӹ޾� �÷��̾��� ���� ������ ���α׷����ٿ�, �ؽ�Ʈ�� ���� �� ǥ���� �� �ֵ��� �ϴ� Ŭ�����Դϴ�.

#pragma once

#include <Components\ProgressBar.h>
#include <Components\TextBlock.h>

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInfoBase.generated.h"

UCLASS()
class ASSASSIN_API UPlayerInfoBase : public UUserWidget
{
	GENERATED_BODY()
private:
	UProgressBar* mHPBar;
	UProgressBar* mMPBar;
	UProgressBar* mSPBar;
	
	UTextBlock* mHPText;
	UTextBlock* mMPText;
	UTextBlock* mSPText;

public:
	virtual void NativeConstruct() override;

public:
	void SetHP(int32 HP, int32 MaxHP);
	void SetMP(int32 MP, int32 MaxMP);
	void SetSP(float SPRatio);
};
