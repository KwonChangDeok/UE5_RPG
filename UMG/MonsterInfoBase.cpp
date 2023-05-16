// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterInfoBase.h"

void UMonsterInfoBase::NativeConstruct()
{
	Super::NativeConstruct();

	mHPBar = Cast<UProgressBar>(GetWidgetFromName(FName(_T("HP"))));
	mName = Cast<UTextBlock>(GetWidgetFromName(FName(_T("Name"))));
	mHPText = Cast<UTextBlock>(GetWidgetFromName(FName(_T("HPText"))));
}

void UMonsterInfoBase::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);
}

void UMonsterInfoBase::SetHP(float HPRatio)
{
	if (IsValid(mHPBar))
	{
		mHPBar->SetPercent(HPRatio);
	}
}

void UMonsterInfoBase::SetName(FText Name)
{
	if (IsValid(mName))
	{
		mName->SetText(Name);
	}
}

void UMonsterInfoBase::SetText(FText Text)
{
	if (IsValid(mHPText))
	{
		mHPText->SetText(Text);
	}
}
