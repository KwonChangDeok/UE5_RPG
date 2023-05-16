// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUIBase.h"

void UMainUIBase::NativeConstruct()
{
	Super::NativeConstruct();

	mPlayerInfo = Cast<UPlayerInfoBase>(GetWidgetFromName(FName(_T("UMG_PlayerInfo"))));

	mSkillCoolDown = Cast<USkillCoolDownBase>(GetWidgetFromName(FName(_T("UMG_SkillCoolTime"))));

	mDashCoolDown = Cast<UDashCoolDownBase>(GetWidgetFromName(FName(_T("UMG_DashCoolTime"))));

	mQuickSlot = Cast<UQuickSlotBase>(GetWidgetFromName(FName(_T("UMG_QuickSlot"))));
}

void UMainUIBase::SetHP(int32 HP, int32 MaxHP)
{
	if (IsValid(mPlayerInfo))
	{
		mPlayerInfo->SetHP(HP, MaxHP);
	}
}

void UMainUIBase::SetMP(int32 MP, int32 MaxMP)
{
	if (IsValid(mPlayerInfo))
	{
		mPlayerInfo->SetMP(MP, MaxMP);
	}
}

void UMainUIBase::SetSP(float SPRatio)
{
	if (IsValid(mPlayerInfo))
	{
		mPlayerInfo->SetSP(SPRatio);
	}
}

void UMainUIBase::SetSkillZBar(float Ratio)
{
	if (IsValid(mSkillCoolDown))
	{
		mSkillCoolDown->SetSkillZBar(Ratio);
	}
}

void UMainUIBase::SetSkillXBar(float Ratio)
{
	if (IsValid(mSkillCoolDown))
	{
		mSkillCoolDown->SetSkillXBar(Ratio);
	}
}

void UMainUIBase::SetSkillCBar(float Ratio)
{
	if (IsValid(mSkillCoolDown))
	{
		mSkillCoolDown->SetSkillCBar(Ratio);
	}
}

void UMainUIBase::SetSkillVBar(float Ratio)
{
	if (IsValid(mSkillCoolDown))
	{
		mSkillCoolDown->SetSkillVBar(Ratio);
	}
}

void UMainUIBase::SetSkillZText(bool Enable)
{
	if (IsValid(mSkillCoolDown))
	{
		mSkillCoolDown->SetSkillZText(Enable);
	}
}

void UMainUIBase::SetSkillXText(bool Enable)
{
	if (IsValid(mSkillCoolDown))
	{
		mSkillCoolDown->SetSkillXText(Enable);
	}
}

void UMainUIBase::SetSkillVBack(FLinearColor Color)
{
	if (IsValid(mSkillCoolDown))
	{
		mSkillCoolDown->SetSkillVBack(Color);
	}
}

void UMainUIBase::SetDashBar(float Ratio)
{
	if (IsValid(mDashCoolDown))
	{
		mDashCoolDown->SetDashBar(Ratio);
	}
}

void UMainUIBase::MouseButtonUp()
{
	if (IsValid(mQuickSlot))
	{
		mQuickSlot->MouseButtonUp();
	}
}

UItemObject* UMainUIBase::GetSlotItem(int32 SlotNum)
{
	if(IsValid(mQuickSlot))
	{
		return mQuickSlot->GetSlotItem(SlotNum);
	}

	return nullptr;
}

void UMainUIBase::ConsumeItem(int32 SlotNum)
{
	if (IsValid(mQuickSlot))
	{
		mQuickSlot->ConsumeItem(SlotNum);
	}
}
