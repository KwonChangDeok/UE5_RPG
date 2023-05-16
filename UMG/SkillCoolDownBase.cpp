// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillCoolDownBase.h"

void USkillCoolDownBase::NativeConstruct()
{
	Super::NativeConstruct();

	mSkillZBar = Cast<UProgressBar>(GetWidgetFromName(FName(_T("SkillZBar"))));
	mSkillXBar = Cast<UProgressBar>(GetWidgetFromName(FName(_T("SkillXBar"))));
	mSkillCBar = Cast<UProgressBar>(GetWidgetFromName(FName(_T("SkillCBar"))));
	mSkillVBar = Cast<UProgressBar>(GetWidgetFromName(FName(_T("SkillVBar"))));

	mSkillZText = Cast<UTextBlock>(GetWidgetFromName(FName(_T("SkillZText"))));
	mSkillXText = Cast<UTextBlock>(GetWidgetFromName(FName(_T("SkillXText"))));

	mSkillZBack = Cast<UImage>(GetWidgetFromName(FName(_T("SkillZBack"))));
	mSkillXBack = Cast<UImage>(GetWidgetFromName(FName(_T("SkillXBack"))));
	mSkillCBack = Cast<UImage>(GetWidgetFromName(FName(_T("SkillCBack"))));
	mSkillVBack = Cast<UImage>(GetWidgetFromName(FName(_T("SkillVBack"))));
}

void USkillCoolDownBase::SetSkillZBar(float Ratio)
{
	if (IsValid(mSkillZBar) && IsValid(mSkillZBack))
	{
		mSkillZBar->SetPercent(Ratio);

		if (Ratio == 0.f)
		{
			FSlateBrush Brush = mSkillZBack->Brush;
			Brush.TintColor = FLinearColor(1.f, 1.f, 1.f, 0.9f);
			mSkillZBack->SetBrush(Brush);
		}
		else
		{
			FSlateBrush Brush = mSkillZBack->Brush;
			Brush.TintColor = FLinearColor(1.f, 1.f, 1.f, 0.5f);
			mSkillZBack->SetBrush(Brush);
		}
	}
}

void USkillCoolDownBase::SetSkillXBar(float Ratio)
{
	if (IsValid(mSkillXBar) && IsValid(mSkillXBack))
	{
		mSkillXBar->SetPercent(Ratio);

		if (Ratio == 0.f)
		{
			FSlateBrush Brush = mSkillXBack->Brush;
			Brush.TintColor = FLinearColor(1.f, 1.f, 1.f, 0.9f);
			mSkillXBack->SetBrush(Brush);
		}
		else
		{
			FSlateBrush Brush = mSkillXBack->Brush;
			Brush.TintColor = FLinearColor(1.f, 1.f, 1.f, 0.5f);
			mSkillXBack->SetBrush(Brush);
		}
	}
}

void USkillCoolDownBase::SetSkillCBar(float Ratio)
{
	if (IsValid(mSkillCBar) && IsValid(mSkillCBack))
	{
		mSkillCBar->SetPercent(Ratio);

		if (Ratio == 0.f)
		{
			FSlateBrush Brush = mSkillCBack->Brush;
			Brush.TintColor = FLinearColor(1.f, 1.f, 1.f, 0.9f);
			mSkillCBack->SetBrush(Brush);
		}
		else
		{
			FSlateBrush Brush = mSkillCBack->Brush;
			Brush.TintColor = FLinearColor(1.f, 1.f, 1.f, 0.5f);
			mSkillCBack->SetBrush(Brush);
		}
	}
}

void USkillCoolDownBase::SetSkillVBar(float Ratio)
{
	if (IsValid(mSkillVBar))
	{
		mSkillCBar->SetPercent(Ratio);
	}
}

void USkillCoolDownBase::SetSkillZText(bool Enable)
{
	if (IsValid(mSkillZText))
	{
		if (Enable)
		{
			mSkillZText->SetColorAndOpacity(FColor::Red);
		}
		else
		{
			mSkillZText->SetColorAndOpacity(FColor::Black);
		}
	}
}

void USkillCoolDownBase::SetSkillXText(bool Enable)
{
	if (IsValid(mSkillXText))
	{
		if (Enable)
		{
			mSkillXText->SetColorAndOpacity(FColor::Red);
		}
		else
		{
			mSkillXText->SetColorAndOpacity(FColor::Black);
		}
	}
}

void USkillCoolDownBase::SetSkillVBack(FLinearColor Color)
{
	if (IsValid(mSkillVBack))
	{
		FSlateBrush Brush = mSkillVBack->Brush;
		Brush.TintColor = Color;
		mSkillVBack->SetBrush(Brush);
	}
}
