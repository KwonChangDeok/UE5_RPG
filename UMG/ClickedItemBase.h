// UserWidget 클래스를 상속받아 아이템 드래그시, 커서 위치에 출력할 아이템의 이미지를 표현하기 위한 클래스입니다.

#pragma once

#include <Components\Image.h>

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "ClickedItemBase.generated.h"

UCLASS()
class ASSASSIN_API UClickedItemBase : public UUserWidget
{
	GENERATED_BODY()
private:
	UImage* mClickedItem;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DT) override;

public:
	void SetClickedItemImage(const FString& ImagePath);
};
