/*
 UserWidget Ŭ������ ��ӹ޾� Ÿ�Ϻ�� ������ ����� �����ϴ� Ŭ�����Դϴ�. 
 �̿ܿ� ���(������ȭ) ������ ���� ��� ���� �����ϸ� ���콺 �̺�Ʈ ó���� ���� �κ��丮 â�� �̵�, 
 Ŀ�� ȣ���� ������ ���� UI��� ������ �巡�� �� ����� ���� �������� ���� ����� �����߽��ϴ�.
*/

#pragma once

#include <Components/TextBlock.h>
#include <Components/TileView.h>
#include <Components/Button.h>

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "InventoryBase.generated.h"

// �κ��丮�� �����ϸ� �̺�Ʈ ó������ Ÿ�Ϻ信�� ���콺 ��ư �ٿ� �̺�Ʈ�� ã�� ���� ������� �޾����ϴ�.
// ���� �̸� Ÿ�Ϻ䰡 �̺�Ʈ�� ó������ �ʵ��� ������ �κ��丮 ����(������������ ���콺 ��ư �ٿ� �̺�Ʈ�� �����߽��ϴ�.)���� 
// ���콺�̺�Ʈ�� ó���ϴ� ������� �ذ��ϰ��� �߽��ϴ�.
// ��� Ÿ�Ϻ��� ������ �ε��� ������ �Ǵ��ϱ� ���� Ŀ���� Ÿ�Ϻ� ������ �Ÿ��� ����Ͽ� �ε����� ���� ������ �������߽��ϴ�.
// ���ϴ� �ٸ� �����ϴ� �Ϳ� ����������, �̴� ���� ���� ����̰�, �и� �𸮾� ������ ����� Ȱ���� ������ �� �� �ִ� ����� �����Ұ��̶� �����մϴ�.
// ���� ������ �ذ��ϸ� ���콺 �̺�Ʈ�� �ֻ�� ������ ó���Ѵٴ� ����� �˰� �Ǿ����� �̷��� ������ ���ͳݿ��� ã�ƺ��� ��������ϴ�.
// �Ի� �� �پ ������ �Բ� ã�ƺ��� ����� ������ �����ϰ� ���� �����ذ��� �ͽ��ϴ�.

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
	// ���忡�� ������ ���콺 ������ ����
	FVector2D AccMousePosition;
	
	// ������ ����Ī�� ���� �ε�������
	int32 OrgIdx;
	int32 DestIdx;

	// ���� ���콺�̺�Ʈ�� ������ �������µ��� �������� ������ ����
	FVector2D AccPosition;

	// ���콺Ŀ���� Ŭ���� ���� �κ��丮�������� �����ǥ��
	FVector2D RelativeLoc;

	FTimerHandle ScrollTimer;
	FTimerHandle CheckTimer;

	// ���� Ŀ���� ��ġ�� Ÿ���� �ε���
	int32 ItemIndex;

	// ���� ȭ�鿡 ������� ũ���, ũ��ڽ��� ũ���� ����
	float Ratio;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;

	// ���콺 �̺�Ʈó��
	// ��, �κ��丮���� ���� �ڽ������� ���ְ�, �ڽ� �ܿ��� ���콺�̺�Ʈ�� �߻���Ű�� ȣ��X

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
	// UI�������� ���콺 �ٽ�ũ�� >> �̶� Ÿ�Ϻ䰡 �̺�Ʈ�� �߻���Ű���� �ϰ�, ���Է��� ���»��·� 0.1�ʰ� ������ �ٽ� �̺�Ʈ��
	// �߻���Ű�� �ʵ��� ����
	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	// �÷��̾�κ��� ���޹޴� �������� �ۿ����� ���콺 �̺�Ʈ
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
	
	// �巡�����̴� �������� ������ ������ �����ϸ� �佺
	void TossItem();
};
