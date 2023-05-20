/*
UserWidget Ŭ������ ��ӹ޾� �Һ� �������� �����Կ� ����ϰ�, 
���� ��ȣ�� �ش��ϴ� Ű�� �Է��� �Ҹ��� �� ������ ���콺 �̺�Ʈ�� �̿��� �������� �巡�� �� ��� ����� ������ Ŭ�����Դϴ�.
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

	// �κ��丮 UI�������� Ŀ�� ����
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	// UI������ Ŀ���� ���, �ٸ� Ŭ�����¿��� ����� ���콺ĸó���̹Ƿ� ȣ��ȵ�.
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	// UI�������� ���콺 Ŭ���ٿ�, �¿츦 �������� ����.
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	// UI�������� ���콺 Ŭ����
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	// UI�������� ���콺 �̵�
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	// �÷��̾�κ��� �Է¹޴� UI���� �� ���콺 ��ư�� �̺�Ʈ
	void MouseButtonUp();

public:
	void ConsumeItem(int32 SlotNum);

	class UItemObject* GetSlotItem(int32 SlotNum)
	{
		return mSlotItem[SlotNum - 1];
	}
};
