/*
UserWidget 클래스를 상속받아 소비 아이템을 퀵슬롯에 등록하고, 
슬롯 번호에 해당하는 키를 입력해 소모할 수 있으며 마우스 이벤트를 이용한 아이템의 드래그 앤 드롭 기능을 구현한 클래스입니다.
*/

#pragma once

#include <Components/TextBlock.h>
#include <Components/Image.h>

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "QuickSlotBase.generated.h"

UCLASS()
class ASSASSIN_API UQuickSlotBase : public UUserWidget
{
	GENERATED_BODY()
private:
	TArray<UImage*> mSlotImage;
	TArray<UTextBlock*> mItemNum;
	TArray<class UItemObject*> mSlotItem;

	FVector2D MousePositionInQuickSlot;
	FVector2D PrevMousePosition;
	FVector2D AccMousePosition;
	int32 SlotIdx;
	int32 ClickedIdx;

	class APlayerCharacter* PlayerCharacter;
	class UItemObject* DragItem;
	class UClickedItemBase* mClickedItem;

	float Ratio;

	bool ClickedInQuickSlot;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime);

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

	// 플레이어로부터 입력받는 UI영역 외 마우스 버튼업 이벤트
	void MouseButtonUp();

public:
	void ConsumeItem(int32 SlotNum);

	class UItemObject* GetSlotItem(int32 SlotNum)
	{
		return mSlotItem[SlotNum - 1];
	}
};
