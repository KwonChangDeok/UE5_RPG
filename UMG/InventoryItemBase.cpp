// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemBase.h"
#include "ItemObject.h"

void UInventoryItemBase::NativeConstruct()
{
	mIconImg = Cast<UImage>(GetWidgetFromName(FName(_T("Icon"))));
	mCountText = Cast<UTextBlock>(GetWidgetFromName(FName(_T("Number"))));
}

void UInventoryItemBase::NativeTick(const FGeometry& _geo, float _DT)
{
	Super::NativeTick(_geo, _DT);
}

void UInventoryItemBase::InitFromData(UObject* _Data)
{
	UItemObject* Data = Cast<UItemObject>(_Data);

	if (IsValid(Data))
	{
		const FString& IconPath = Data->GetIconPath();
		int32 Count = Data->GetItemCount();

		UTexture2D* pTex2D = LoadObject<UTexture2D>(nullptr, *IconPath);
		if (IsValid(pTex2D))
		{
			mIconImg->SetBrushFromTexture(pTex2D);
		}
		
		mCountText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Count)));
	}
}
