// Fill out your copyright notice in the Description page of Project Settings.


#include "DashCoolDownBase.h"

void UDashCoolDownBase::NativeConstruct()
{
	Super::NativeConstruct();

	mDashBar = Cast<UProgressBar>(GetWidgetFromName(FName(_T("DashBar"))));
	mDashBack = Cast<UImage>(GetWidgetFromName(FName(_T("DashBack"))));
}

void UDashCoolDownBase::SetDashBar(float Ratio)
{
	if (IsValid(mDashBar) && IsValid(mDashBack))
	{
		mDashBar->SetPercent(Ratio);

		if (Ratio == 0.f)
		{
			FSlateBrush Brush = mDashBack->Brush;
			Brush.TintColor = FLinearColor(1.f, 1.f, 1.f, 0.9f);
			mDashBack->SetBrush(Brush);
		}
		else
		{
			FSlateBrush Brush = mDashBack->Brush;
			Brush.TintColor = FLinearColor(1.f, 1.f, 1.f, 0.5f);
			mDashBack->SetBrush(Brush);
		}
	}
}