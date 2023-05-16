// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterDamageBase.h"

void UMonsterDamageBase::NativeConstruct()
{
	Super::NativeConstruct();

	mDamage = Cast<UTextBlock>(GetWidgetFromName(FName(_T("Damage"))));
	mDamage->SetVisibility(ESlateVisibility::Hidden);
}

void UMonsterDamageBase::SetDamage(FText Damage)
{
	if (IsValid(mDamage))
	{
		mDamage->SetText(Damage);
		mDamage->SetColorAndOpacity(FColor::Orange);
		mDamage->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMonsterDamageBase::SetCriticalDamage(FText Damage)
{
	if (IsValid(mDamage))
	{
		mDamage->SetText(Damage);
		mDamage->SetColorAndOpacity(FColor::Red);
		mDamage->SetVisibility(ESlateVisibility::Visible);
	}
}