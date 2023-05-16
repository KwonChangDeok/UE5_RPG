// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotBase.h"
#include "InventoryBase.h"
#include "../Player/PlayerCharacter.h"
#include "ItemObject.h"
#include "ClickedItembase.h"

void UQuickSlotBase::NativeConstruct()
{
	Super::NativeConstruct();

	mSlotImage.Add(Cast<UImage>(GetWidgetFromName(FName(_T("Slot1")))));
	mSlotImage.Add(Cast<UImage>(GetWidgetFromName(FName(_T("Slot2")))));
	mSlotImage.Add(Cast<UImage>(GetWidgetFromName(FName(_T("Slot3")))));
	mSlotImage.Add(Cast<UImage>(GetWidgetFromName(FName(_T("Slot4")))));

	mItemNum.Add(Cast<UTextBlock>(GetWidgetFromName(FName(_T("ItemNum1")))));
	mItemNum.Add(Cast<UTextBlock>(GetWidgetFromName(FName(_T("ItemNum2")))));
	mItemNum.Add(Cast<UTextBlock>(GetWidgetFromName(FName(_T("ItemNum3")))));
	mItemNum.Add(Cast<UTextBlock>(GetWidgetFromName(FName(_T("ItemNum4")))));

	for (int32 i = 0; i < 4; i++)
	{
		mSlotItem.Add(nullptr);
	}

	mClickedItem = Cast<UClickedItemBase>(GetWidgetFromName(FName(_T("UMG_ClickedItem"))));
	mClickedItem->SetVisibility(ESlateVisibility::Hidden);

	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UQuickSlotBase::NativeTick(const FGeometry& Geometry, float DeltaTime)
{
	Super::NativeTick(Geometry, DeltaTime);

	// 위젯영역 밖으로 나갈 수 있게
	if (ClickedInQuickSlot)
	{
		if (IsValid(mClickedItem))
		{
			FVector2D MousePosition;
			GetWorld()->GetGameViewport()->GetMousePosition(MousePosition);

			if (PrevMousePosition != FVector2D::ZeroVector)
			{
				AccMousePosition = AccMousePosition + MousePosition - PrevMousePosition;
			}

			FWidgetTransform Transform;
			Transform.Translation = (AccMousePosition + MousePositionInQuickSlot) * Ratio;
			mClickedItem->SetRenderTransform(Transform);

			GetWorld()->GetGameViewport()->GetMousePosition(PrevMousePosition);
		}
	}
	// 위젯 영역 내부로만 영역 제한
	else
	{
		if (IsValid(mClickedItem))
		{
			FWidgetTransform Transform;
			Transform.Translation = MousePositionInQuickSlot * Ratio;
			mClickedItem->SetRenderTransform(Transform);

			GetWorld()->GetGameViewport()->GetMousePosition(PrevMousePosition);
		}
	}
}

void UQuickSlotBase::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	AccMousePosition = FVector2D::ZeroVector;
	PrevMousePosition = FVector2D::ZeroVector;

	Ratio = 385.0/ GetCachedGeometry().GetAbsoluteSize().X;

	if (IsValid(PlayerCharacter))
	{
		UItemObject* temp = PlayerCharacter->GetDragItem();
		if (IsValid(temp))
		{
			DragItem = NewObject<UItemObject>();
			DragItem->SetIconPath(temp->GetIconPath());
			DragItem->SetItemCount(temp->GetItemCount());
			DragItem->SetItemName(temp->GetItemName());
			DragItem->SetItemDescription(temp->GetItemDescription());
			DragItem->SetItemID(temp->GetItemID());
			DragItem->SetIsBlank(temp->GetIsBlank());
		}
		else
		{
			return;
		}

		if (IsValid(DragItem))
		{
			if (IsValid(mClickedItem))
			{
				mClickedItem->SetClickedItemImage(DragItem->GetIconPath());
				mClickedItem->SetRenderTranslation(MousePositionInQuickSlot * Ratio);
				mClickedItem->SetVisibility(ESlateVisibility::HitTestInvisible);
				ClickedInQuickSlot = false;
			}
			PlayerCharacter->TossItem();
		}
	}
}

void UQuickSlotBase::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	AccMousePosition = FVector2D::ZeroVector;
	PrevMousePosition = FVector2D::ZeroVector;
}

FReply UQuickSlotBase::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	ClickedInQuickSlot = true;

	ClickedIdx = SlotIdx;

	if (IsValid(mSlotItem[ClickedIdx]))
	{
		if (!mSlotItem[ClickedIdx]->GetIsBlank())
		{
			DragItem = mSlotItem[ClickedIdx];
			if (IsValid(DragItem))
			{
				if (IsValid(mClickedItem))
				{
					mClickedItem->SetClickedItemImage(DragItem->GetIconPath());
					mClickedItem->SetRenderTranslation(MousePositionInQuickSlot * Ratio);
					mClickedItem->SetVisibility(ESlateVisibility::HitTestInvisible);
				}
			}
		}
	}

	return FReply::Handled();
}

FReply UQuickSlotBase::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	ClickedInQuickSlot = false;

	if (IsValid(DragItem))
	{
		for (int32 i = 0; i < 4; i++)
		{
			// 이미 슬롯에 같은 아이템이 존재한다면 기존아이템 제거 후 재등록
			if (IsValid(mSlotItem[i]))
			{
				if (mSlotItem[i]->GetItemID() == DragItem->GetItemID())
				{
					mSlotItem[i] = nullptr;
					UTexture2D* pTex2D = LoadObject<UTexture2D>(nullptr, _T("Texture2D'/Game/Collections/Blank.Blank'"));
					if (IsValid(pTex2D))
					{
						mSlotImage[i]->SetBrushFromTexture(pTex2D);
						mItemNum[i]->SetText(FText::AsNumber(0));
					}
				}
			}
		}

		mSlotItem[SlotIdx] = DragItem;

		UTexture2D* pTex2D = LoadObject<UTexture2D>(nullptr, *DragItem->GetIconPath());
		if (IsValid(pTex2D))
		{
			if (IsValid(mSlotImage[SlotIdx]))
			{
				mSlotImage[SlotIdx]->SetBrushFromTexture(pTex2D);
			}
		}

		if (IsValid(mItemNum[SlotIdx]))
		{
			mItemNum[SlotIdx]->SetText(FText::AsNumber(DragItem->GetItemCount()));
		}

		if (IsValid(mClickedItem))
		{
			mClickedItem->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	DragItem = nullptr;

	return FReply::Handled();
}

FReply UQuickSlotBase::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);

	MousePositionInQuickSlot = InMouseEvent.GetScreenSpacePosition() - InGeometry.GetAbsolutePosition();

	SlotIdx = MousePositionInQuickSlot.X / (InGeometry.GetAbsoluteSize().X / 4);

	return FReply::Handled();
}

void UQuickSlotBase::MouseButtonUp()
{
	if (ClickedInQuickSlot)
	{
		mSlotItem[ClickedIdx] = nullptr;

		UTexture2D* pTex2D = LoadObject<UTexture2D>(nullptr, _T("Texture2D'/Game/Collections/Blank.Blank'"));
		if (IsValid(pTex2D))
		{
			mSlotImage[ClickedIdx]->SetBrushFromTexture(pTex2D);
			mItemNum[ClickedIdx]->SetText(FText::AsNumber(0));
			mClickedItem->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	ClickedInQuickSlot = false;
	DragItem = nullptr;
}

void UQuickSlotBase::ConsumeItem(int32 SlotNum)
{
	if (IsValid(mItemNum[SlotNum-1]) && IsValid(mSlotItem[SlotNum-1]))
	{
		int32 CurNum = mSlotItem[SlotNum-1]->GetItemCount();

		mItemNum[SlotNum-1]->SetText(FText::AsNumber(CurNum -1));
		mSlotItem[SlotNum-1]->SetItemCount(CurNum - 1);
	}
}
