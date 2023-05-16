// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickedItemBase.h"

void UClickedItemBase::NativeConstruct()
{
	Super::NativeConstruct();

	mClickedItem = Cast<UImage>(GetWidgetFromName(FName(_T("ClickedItem"))));
}

void UClickedItemBase::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);
}

void UClickedItemBase::SetClickedItemImage(const FString& ImagePath)
{
	UTexture2D* pTex2D = LoadObject<UTexture2D>(nullptr, *ImagePath);
	if (IsValid(pTex2D))
	{
		if (IsValid(mClickedItem))
		{
			mClickedItem->SetBrushFromTexture(pTex2D);
		}
	}
}
