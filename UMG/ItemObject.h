// Object 클래스를 상속받아 구현한 인벤토리 내 아이템 객체입니다. 
// 아이템의 수량, 아이콘 경로, 아이템명과 설명, 고유ID등의 정보를 가지고 있습니다.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "ItemObject.generated.h"

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
