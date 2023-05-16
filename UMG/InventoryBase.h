// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components/TextBlock.h>
#include <Components/TileView.h>
#include <Components/Button.h>

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "InventoryBase.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API UInventoryBase : public UUserWidget
{
	GENERATED_BODY()
private:
	UTileView* mTileView;
	class UInventoryItemBase* mInventoryItem;
	class UItemDescriptionBase* mItemDescription;
	UTextBlock* mGoldText;
	class UClickedItemBase* mClickedItem;
	UButton* mSortButton;

	class APlayerCharacter* PlayerCharacter;

	bool CursorOnUI;
	bool bFrameClicked;
	bool bItemClicked;
	bool CursorOnTile;

	FVector2D TileLocRelativeInven;
	FVector2D MousePositionInTile;
	FVector2D MousePositionInScreen;
	FVector2D PrevMousePosition;
	// 월드에서 가져온 마우스 변위를 누적
	FVector2D AccMousePosition;
	
	// 아이템 스위칭을 위한 인덱스정보
	int32 OrgIdx;
	int32 DestIdx;

	// 월드 마우스이벤트가 위젯에 가려지는동안 움직임을 누적할 변수
	FVector2D AccPosition;

	// 마우스커서로 클릭한 곳과 인벤토리위젯사이 상대좌표값
	FVector2D RelativeLoc;

	FTimerHandle ScrollTimer;
	FTimerHandle CheckTimer;

	// 현재 커서가 위치한 타일의 인덱스
	int32 ItemIndex;

	// 현재 화면에 출력중인 크기와, 크기박스상 크기의 비율
	float Ratio;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;

	// 마우스 이벤트처리
	// 단, 인벤토리위젯 위에 자식위젯이 떠있고, 자식 단에서 마우스이벤트를 발생시키면 호출X

	// 인벤토리 UI영역으로 커서 진입
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	// UI영역을 커서가 벗어남, 다만 클릭상태에서 벗어나면 마우스캡처중이므로 호출안됨.
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	// UI영역에서 마우스 클릭다운, 좌우를 구분하지 않음.
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	// UI영역에서 마우스 클릭업
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	// UI영역에서 마우스 이동
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	// UI영역에서 마우스 휠스크롤 >> 이때 타일뷰가 이벤트를 발생시키도록 하고, 휠입력이 없는상태로 0.1초가 지나면 다시 이벤트를
	// 발생시키지 않도록 구현
	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	// 플레이어로부터 전달받는 위젯영역 밖에서의 마우스 이벤트
	void MouseButtonUp();

public:
	void AddItem(FItemDataInfo ItemInfo);

	void EditItem(EITEM_ID ID, int32 count);

	bool GetCursorOnUI()
	{
		return CursorOnUI;
	}

	void SetGold(int32 Gold);

public:
	UFUNCTION()
	void InitItem(UItemObject* NewItem, FTimerHandle ItemTimer);

	UFUNCTION()
	void OnListViewScrolled(float ScrollOffset, float ScrollDelta);

	UFUNCTION()
	void OnSortButtonClicked();

	void ScrollEnd();

	void CheckScroll();
	
	// 드래그중이던 아이템이 퀵슬롯 영역에 진입하면 토스
	void TossItem();
};
