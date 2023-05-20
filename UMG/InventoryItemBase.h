// UserWidget 클래스를 상속받아 구현한 InventoryBase 타일뷰의 엔트리 위젯 클래스의 부모 클래스입니다.

#pragma once

#include <Components/Image.h>
#include <Components/TextBlock.h>

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemBase.generated.h"

UCLASS()
class ASSASSIN_API UInventoryItemBase : public UUserWidget
{
	GENERATED_BODY()
private:
	UImage* mIconImg;
	UTextBlock* mCountText;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DT) override;

public:
	UFUNCTION(BlueprintCallable)
	void InitFromData(UObject* _Data);
};
