// UserWidget Ŭ������ ��ӹ޾� ������ �巡�׽�, Ŀ�� ��ġ�� ����� �������� �̹����� ǥ���ϱ� ���� Ŭ�����Դϴ�.

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
