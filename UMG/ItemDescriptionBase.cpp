// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDescriptionBase.h"

void UItemDescriptionBase::NativeConstruct()
{
	Super::NativeConstruct();

	mItemName = Cast<UTextBlock>(GetWidgetFromName(FName(_T("ItemName"))));
	mItemDescription = Cast<UTextBlock>(GetWidgetFromName(FName(_T("ItemDescription"))));
	mItemIcon = Cast<UImage>(GetWidgetFromName(FName(_T("ItemIcon"))));
}

void UItemDescriptionBase::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);
}

void UItemDescriptionBase::SetItemName(FText Name)
{
	if (IsValid(mItemName))
	{
		mItemName->SetText(Name);
	}
}

void UItemDescriptionBase::SetItemDescription(FText Description)
{
	if (IsValid(mItemDescription))
	{
		mItemDescription->SetText(Description);
	}
}

void UItemDescriptionBase::SetItemIcon(const FString& ImagePath)
{
	if (IsValid(mItemIcon))
	{
		UTexture2D* Texture = LoadObject<UTexture2D>(nullptr, *ImagePath);
		FSlateBrush Brush;
		Brush.SetResourceObject(Texture);
		mItemIcon->SetBrushFromTexture(Texture);
	}
}
