// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "ItemObject.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API UItemObject : public UObject
{
	GENERATED_BODY()
public:
	UItemObject();

private:
	FString	mIconPath;		// 아이콘 이미지 경로
	int32 mCount;	// 아이템 수량

	FString mItemName;
	FString mItemDescription;

	EITEM_ID mItemID;

	bool IsBlank;

public:
	void SetIconPath(const FString& _IconPath)
	{
		mIconPath = _IconPath;
	}
	const FString& GetIconPath()
	{ 
		return mIconPath; 
	}

	void SetItemCount(int32 _Count)
	{
		mCount = _Count;
	}
	int32 GetItemCount()
	{
		return mCount;
	}

	void SetItemName(const FString& _ItemName)
	{
		mItemName = _ItemName;
	}
	const FString& GetItemName()
	{
		return mItemName;
	}

	void SetItemDescription(const FString& _ItemDescription)
	{
		mItemDescription = _ItemDescription;
	}
	const FString& GetItemDescription()
	{
		return mItemDescription;
	}

	void SetIsBlank(bool Type)
	{
		IsBlank = Type;
	}
	bool GetIsBlank()
	{
		return IsBlank;
	}

	void SetItemID(EITEM_ID ID)
	{
		mItemID = ID;
	}
	EITEM_ID GetItemID()
	{
		return mItemID;
	}
};
