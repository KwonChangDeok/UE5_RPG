// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryBase.h"
#include "ItemObject.h"
#include "InventoryItemBase.h"
#include "ItemDescriptionBase.h"
#include "ClickedItemBase.h"
#include "../Player/PlayerCharacter.h"

void UInventoryBase::NativeConstruct()
{
	Super::NativeConstruct();

	mTileView = Cast<UTileView>(GetWidgetFromName(FName(_T("TileView"))));
	mTileView->SetVisibility(ESlateVisibility::HitTestInvisible);

	mTileView->OnListViewScrolled().AddUObject(this, &UInventoryBase::OnListViewScrolled);

	mItemDescription = Cast<UItemDescriptionBase>(GetWidgetFromName(FName(_T("UMG_ItemDescription"))));
	mItemDescription->SetVisibility(ESlateVisibility::Hidden);

	mClickedItem = Cast<UClickedItemBase>(GetWidgetFromName(FName(_T("UMG_ClickedItem"))));
	mClickedItem->SetVisibility(ESlateVisibility::Hidden);

	mSortButton = Cast<UButton>(GetWidgetFromName(FName(_T("SortButton"))));
	mSortButton->OnClicked.AddDynamic(this, &UInventoryBase::OnSortButtonClicked);

	CursorOnUI = false;
	bFrameClicked = false;
	bItemClicked = false;

	mGoldText = Cast<UTextBlock>(GetWidgetFromName(FName(_T("GoldText"))));

	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	TileLocRelativeInven = FVector2D::ZeroVector;
}

void UInventoryBase::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);

	// 프레임 드래그 이동
	if (bFrameClicked)
	{
		FVector2D MousePosition;
		GetWorld()->GetGameViewport()->GetMousePosition(MousePosition);

		SetPositionInViewport(MousePosition + AccPosition - RelativeLoc);
	}
	else if (bItemClicked)
	{
		if (IsValid(mClickedItem))
		{
			FVector2D MousePosition;
			GetWorld()->GetGameViewport()->GetMousePosition(MousePosition);

			if(PrevMousePosition != FVector2D::ZeroVector)
			{
				AccMousePosition = AccMousePosition + MousePosition - PrevMousePosition;
			}

			FWidgetTransform Transform;
			Transform.Translation = (AccMousePosition + MousePositionInTile) * Ratio;
			mClickedItem->SetRenderTransform(Transform);

			GetWorld()->GetGameViewport()->GetMousePosition(PrevMousePosition);
		}
	}
}

void UInventoryBase::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	CursorOnUI = true;

	if (IsValid(mTileView))
	{
		TileLocRelativeInven = mTileView->GetCachedGeometry().GetAbsolutePosition() - GetCachedGeometry().GetAbsolutePosition();
	}

	AccMousePosition = FVector2D::ZeroVector;
	PrevMousePosition = FVector2D::ZeroVector;

	Ratio = 800.0 / GetCachedGeometry().GetAbsoluteSize().X;
}

void UInventoryBase::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	CursorOnUI = false;

	AccMousePosition = FVector2D::ZeroVector;
	PrevMousePosition = FVector2D::ZeroVector;

	AccPosition = FVector2D::ZeroVector;
}

FReply UInventoryBase::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	RelativeLoc = InMouseEvent.GetScreenSpacePosition() - GetCachedGeometry().GetAbsolutePosition();

	// 타일뷰 내부에서 클릭된것이라면
	if (CursorOnTile)
	{
		bFrameClicked = false;

		if (IsValid(mTileView))
		{
			UItemObject* ClickedItem = Cast<UItemObject>(mTileView->GetItemAt(ItemIndex));
			if (IsValid(ClickedItem) && !ClickedItem->GetIsBlank())
			{
				bItemClicked = true;
				OrgIdx = ItemIndex;

				if (IsValid(mClickedItem))
				{
					mClickedItem->SetClickedItemImage(ClickedItem->GetIconPath());
					mClickedItem->SetRenderTranslation(RelativeLoc*Ratio);
					mClickedItem->SetVisibility(ESlateVisibility::HitTestInvisible);

					if (IsValid(PlayerCharacter))
					{
						PlayerCharacter->SetDragItem(ClickedItem);
					}
				}
			}
		}

	}
	// 그렇지않다면
	else
	{
		bItemClicked = false;
		bFrameClicked = true;
	}

	return FReply::Handled();
}

FReply UInventoryBase::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	bFrameClicked = false;

	if (bItemClicked && IsValid(mTileView))
	{
		UItemObject* DropedItem = Cast<UItemObject>(mTileView->GetItemAt(ItemIndex));
		{
			if(IsValid(DropedItem))
			{
				UItemObject* OrgItem = Cast<UItemObject>(mTileView->GetItemAt(OrgIdx));
				UItemObject* temp = NewObject<UItemObject>();

				// 원본 내용 지역변수에 저장
				temp->SetIconPath(OrgItem->GetIconPath());
				temp->SetItemCount(OrgItem->GetItemCount());
				temp->SetItemName(OrgItem->GetItemName());
				temp->SetItemDescription(OrgItem->GetItemDescription());
				temp->SetItemID(OrgItem->GetItemID());
				temp->SetIsBlank(OrgItem->GetIsBlank());

				// 원본에 드랍지점아이템 내용 복사
				OrgItem->SetIconPath(DropedItem->GetIconPath());
				OrgItem->SetItemCount(DropedItem->GetItemCount());
				OrgItem->SetItemName(DropedItem->GetItemName());
				OrgItem->SetItemDescription(DropedItem->GetItemDescription());
				OrgItem->SetItemID(DropedItem->GetItemID());
				OrgItem->SetIsBlank(DropedItem->GetIsBlank());

				// 드랍지점아이템에 원본 저장내용 복사
				DropedItem->SetIconPath(temp->GetIconPath());
				DropedItem->SetItemCount(temp->GetItemCount());
				DropedItem->SetItemName(temp->GetItemName());
				DropedItem->SetItemDescription(temp->GetItemDescription());
				DropedItem->SetItemID(temp->GetItemID());
				DropedItem->SetIsBlank(temp->GetIsBlank());

				if (IsValid(mClickedItem))
				{
					mClickedItem->SetVisibility(ESlateVisibility::Hidden);
				}

				if (IsValid(PlayerCharacter))
				{
					PlayerCharacter->SetDragItem(nullptr);
				}
			}
		}

		bItemClicked = false;
	}

	return FReply::Handled();
}

FReply UInventoryBase::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);

	if (CursorOnUI)
	{
		AccPosition += InMouseEvent.GetCursorDelta();
	}

	MousePositionInTile = InMouseEvent.GetScreenSpacePosition() - mTileView->GetCachedGeometry().GetAbsolutePosition();

	// 커서가 타일뷰 내부에 있다면
	if (MousePositionInTile.Y > 0.f && MousePositionInTile.Y < mTileView->GetCachedGeometry().GetAbsoluteSize().Y)
	{
		CursorOnTile = true;

		float PixelSize = mTileView->GetCachedGeometry().GetAbsoluteSize().Y / 7.75;
		int32 Idx_X = MousePositionInTile.X / (mTileView->GetCachedGeometry().GetAbsoluteSize().X/6);
		int32 Idx_Y = (MousePositionInTile.Y + mTileView->GetScrollOffset()*0.167* PixelSize) / PixelSize;

		// 글로벌인덱스
		ItemIndex = 6 * Idx_Y + Idx_X;

		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, FString::FromInt(Index));

		UItemObject* HoveredItem = Cast<UItemObject>(mTileView->GetItemAt(ItemIndex));

		if (IsValid(HoveredItem))
		{
			// 빈칸이거나 아이템을 클릭한 상태라면 아이템설명을 표시하지 않는다.
			if (!HoveredItem->GetIsBlank() && IsValid(mItemDescription) && !bItemClicked)
			{
				mItemDescription->SetItemDescription(FText::FromString(HoveredItem->GetItemDescription()));
				mItemDescription->SetItemName(FText::FromString(HoveredItem->GetItemName()));
				mItemDescription->SetItemIcon(HoveredItem->GetIconPath());
				mItemDescription->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				mItemDescription->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
	else
	{
		CursorOnTile = false;
	}

	return FReply::Handled();
}

FReply UInventoryBase::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseWheel(InGeometry, InMouseEvent);

	if (IsValid(mTileView))
	{
		mTileView->SetVisibility(ESlateVisibility::Visible);

		GetWorld()->GetTimerManager().SetTimer(CheckTimer, this, &UInventoryBase::CheckScroll, 0.1f, false, -1.f);
	}

	return FReply::Handled();
}

// 플레이어로부터 입력받는 위젯 외부의 마우스버튼업 이벤트
void UInventoryBase::MouseButtonUp()
{
	bFrameClicked = false;
	bItemClicked = false;
	AccPosition = FVector2D::ZeroVector;

	if (IsValid(mClickedItem))
	{
		mClickedItem->SetVisibility(ESlateVisibility::Hidden);
	}

	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->SetDragItem(nullptr);
	}
}

void UInventoryBase::AddItem(FItemDataInfo ItemInfo)
{
	if (ItemInfo.ItemType == EITEM_TYPE::Blank)
	{
		UItemObject* NewItem = NewObject<UItemObject>();

		NewItem->SetIconPath(ItemInfo.IconPath);
		NewItem->SetItemCount(ItemInfo.NumberOfItem);
		NewItem->SetItemName(ItemInfo.ItemName);
		NewItem->SetItemDescription(ItemInfo.Description);
		NewItem->SetItemID(ItemInfo.ID);
		NewItem->SetIsBlank(true);

		mTileView->AddItem(NewItem);

		FTimerHandle ItemTimer;

		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUObject(this, &UInventoryBase::InitItem, NewItem, ItemTimer);

		GetWorld()->GetTimerManager().SetTimer(ItemTimer, TimerDelegate, 0.1f, true, -1.f);
	}
	else
	{
		for (int32 i = 0; i < mTileView->GetNumItems(); i++)
		{
			UItemObject* Item = Cast<UItemObject>(mTileView->GetItemAt(i));
			if (IsValid(Item))
			{
				if (Item->GetIsBlank())
				{
					Item->SetIconPath(ItemInfo.IconPath);
					Item->SetItemCount(ItemInfo.NumberOfItem);
					Item->SetItemName(ItemInfo.ItemName);
					Item->SetItemDescription(ItemInfo.Description);
					Item->SetItemID(ItemInfo.ID);
					Item->SetIsBlank(false);
					break;
				}
			}
		}
	}
}

void UInventoryBase::EditItem(EITEM_ID ID, int32 count)
{
	for (int32 i = 0; i < mTileView->GetNumItems(); i++)
	{
		UItemObject* Item = Cast<UItemObject>(mTileView->GetItemAt(i));
		if (IsValid(Item))
		{
			if (Item->GetItemID() == ID)
			{
				if (count == 0)
				{
					Item->SetIconPath(_T("Texture2D'/Game/Collections/Blank.Blank'"));
					Item->SetItemCount(0);
					Item->SetItemName((_T("")));
					Item->SetItemDescription(_T(""));
					Item->SetItemID(EITEM_ID::Blank);
					Item->SetIsBlank(true);
				}
				else
				{
					Item->SetItemCount(count);
				}
				break;
			}
		}
	}
}

void UInventoryBase::SetGold(int32 Gold)
{
	FString str = FString::FromInt(Gold);
	int32 HeadNum = str.Len() % 3;
	FString AnsStr;
	for (int32 i = 0; i < str.Len(); i++)
	{
		if ((i % 3) == HeadNum && i != 0)
		{
			AnsStr += _T(",");
		}

		AnsStr += str[i];
	}

	if (IsValid(mGoldText))
	{
		mGoldText->SetText(FText::FromString(AnsStr));
	}
}

void UInventoryBase::InitItem(UItemObject* NewItem, FTimerHandle ItemTimer)
{
	mInventoryItem = Cast<UInventoryItemBase>(mTileView->GetEntryWidgetFromItem(NewItem));
	
	if (IsValid(mInventoryItem))
	{
		mInventoryItem->InitFromData(NewItem);
		GetWorld()->GetTimerManager().ClearTimer(ItemTimer);
	}
}

void UInventoryBase::OnListViewScrolled(float ScrollOffset, float ScrollDelta)
{
	GetWorld()->GetTimerManager().SetTimer(ScrollTimer, this, &UInventoryBase::ScrollEnd, 0.01f, false, -1.f);
}

void UInventoryBase::OnSortButtonClicked()
{
	for (int32 i = 1; i < mTileView->GetNumItems(); i++)
	{
		for (int32 j = i; j > 0; j--)
		{
			UItemObject* src = Cast<UItemObject>(mTileView->GetItemAt(j));
			UItemObject* cmp = Cast<UItemObject>(mTileView->GetItemAt(j - 1));

			if (IsValid(src) && IsValid(cmp))
			{
				if (src->GetIsBlank())
				{
					break;
				}

				if (src->GetItemID() < cmp->GetItemID())
				{
					UItemObject* temp = NewObject<UItemObject>();

					// 원본 내용 지역변수에 저장
					temp->SetIconPath(src->GetIconPath());
					temp->SetItemCount(src->GetItemCount());
					temp->SetItemName(src->GetItemName());
					temp->SetItemDescription(src->GetItemDescription());
					temp->SetItemID(src->GetItemID());
					temp->SetIsBlank(src->GetIsBlank());

					// 원본에 비교아이템 내용 복사
					src->SetIconPath(cmp->GetIconPath());
					src->SetItemCount(cmp->GetItemCount());
					src->SetItemName(cmp->GetItemName());
					src->SetItemDescription(cmp->GetItemDescription());
					src->SetItemID(cmp->GetItemID());
					src->SetIsBlank(cmp->GetIsBlank());

					// 비교아이템에 원본 저장내용 복사
					cmp->SetIconPath(temp->GetIconPath());
					cmp->SetItemCount(temp->GetItemCount());
					cmp->SetItemName(temp->GetItemName());
					cmp->SetItemDescription(temp->GetItemDescription());
					cmp->SetItemID(temp->GetItemID());
					cmp->SetIsBlank(temp->GetIsBlank());
				}
			}
		}
	}
}

void UInventoryBase::ScrollEnd()
{
	if (IsValid(mTileView))
	{
		mTileView->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UInventoryBase::CheckScroll()
{
	if (IsValid(mTileView))
	{
		int32 offset = mTileView->GetScrollOffset();

		if (offset == 0 || offset == 13)
		{
			mTileView->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
	}
}

void UInventoryBase::TossItem()
{
	bFrameClicked = false;
	bItemClicked = false;
	AccPosition = FVector2D::ZeroVector;

	if (IsValid(mClickedItem))
	{
		mClickedItem->SetVisibility(ESlateVisibility::Hidden);
	}

	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->SetDragItem(nullptr);
	}
}
