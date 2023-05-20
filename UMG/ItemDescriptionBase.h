// UserWidget 클래스를 상속받아 아이템의 설명 UI를 표현하기 위한 텍스트 블록과 이미지를 설정해주는 클래스입니다.

#pragma once

#include <Components\TextBlock.h>
#include <Components\Image.h>

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "ItemDescriptionBase.generated.h"

UCLASS()
class ASSASSIN_API UItemDescriptionBase : public UUserWidget
{
	GENERATED_BODY()
private:
	UTextBlock* mItemName;
	UTextBlock* mItemDescription;
	UImage* mItemIcon;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime);

public:
	void SetItemName(FText Name);
	void SetItemDescription(FText Description);
	void SetItemIcon(const FString& ImagePath);
};
