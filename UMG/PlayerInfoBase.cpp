// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInfoBase.h"

void UPlayerInfoBase::NativeConstruct()
{
	Super::NativeConstruct();

	mHPBar = Cast<UProgressBar>(GetWidgetFromName(FName(_T("HP"))));
	mMPBar = Cast<UProgressBar>(GetWidgetFromName(FName(_T("MP"))));
	mSPBar = Cast<UProgressBar>(GetWidgetFromName(FName(_T("SP"))));

	mHPText = Cast<UTextBlock>(GetWidgetFromName(FName(_T("HPText"))));
	mMPText = Cast<UTextBlock>(GetWidgetFromName(FName(_T("MPText"))));
	mSPText = Cast<UTextBlock>(GetWidgetFromName(FName(_T("SPText"))));
}

void UPlayerInfoBase::SetHP(int32 HP, int32 MaxHP)
{
	if (IsValid(mHPBar))
	{
		mHPBar->SetPercent(HP/(float)MaxHP);
		FString temp = FString::FromInt(HP) + FString(" / ") + FString::FromInt(MaxHP);
		mHPText->SetText(FText::FromString(temp));
	}
}

void UPlayerInfoBase::SetMP(int32 MP, int32 MaxMP)
{
	if (IsValid(mMPBar))
	{
		mMPBar->SetPercent(MP/(float)MaxMP);
		FString temp = FString::FromInt(MP) + FString(" / ") + FString::FromInt(MaxMP);
		mMPText->SetText(FText::FromString(temp));
	}
}

void UPlayerInfoBase::SetSP(float SPRatio)
{
	if (IsValid(mSPBar))
	{
		mSPBar->SetPercent(SPRatio);
		FString temp = FString::FromInt(int32(100 * SPRatio)) + FString(" / ") + FString::FromInt(100);
		mSPText->SetText(FText::FromString(temp));
	}
}
