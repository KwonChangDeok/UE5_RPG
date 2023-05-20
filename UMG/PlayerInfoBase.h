// UserWidget 클래스를 상속받아 플레이어의 상태 정보를 프로그래스바와, 텍스트를 설정 해 표현할 수 있도록 하는 클래스입니다.

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
