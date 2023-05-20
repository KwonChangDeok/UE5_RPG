// UserWidget Ŭ������ ��ӹ޾� ������ InventoryBase Ÿ�Ϻ��� ��Ʈ�� ���� Ŭ������ �θ� Ŭ�����Դϴ�.

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
