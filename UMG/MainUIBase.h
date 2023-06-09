// UserWidget 클래스를 상속받아 플레이어 상태 정보, 스킬쿨타임 정보, 퀵슬롯 정보 등의 유저 위젯을 포함하는 메인 UI 클래스입니다.

#pragma once

#include <Blueprint\UserWidget.h>

#include "PlayerInfoBase.h"
#include "SkillCoolDownBase.h"
#include "DashCoolDownBase.h"
#include "QuickSlotBase.h"

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "MainUIBase.generated.h"

UCLASS()
class ASSASSIN_API UMainUIBase : public UUserWidget
{
	GENERATED_BODY()
private:
	UPlayerInfoBase* mPlayerInfo;
	USkillCoolDownBase* mSkillCoolDown;
	UDashCoolDownBase* mDashCoolDown;
	UQuickSlotBase* mQuickSlot;

public:
	virtual void NativeConstruct() override;

public:
	void SetHP(int32 HP, int32 MaxHP);
	void SetMP(int32 MP, int32 MaxMP);
	void SetSP(float SPRatio);

	void SetSkillZBar(float Ratio);
	void SetSkillXBar(float Ratio);
	void SetSkillCBar(float Ratio);
	void SetSkillVBar(float Ratio);

	void SetSkillZText(bool Enable);
	void SetSkillXText(bool Enable);

	void SetSkillVBack(FLinearColor Color);

	void SetDashBar(float Ratio);

	void MouseButtonUp();

	class UItemObject* GetSlotItem(int32 SlotNum);

	void ConsumeItem(int32 SlotNum);
};
