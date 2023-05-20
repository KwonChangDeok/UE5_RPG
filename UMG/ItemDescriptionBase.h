// UserWidget Ŭ������ ��ӹ޾� �������� ���� UI�� ǥ���ϱ� ���� �ؽ�Ʈ ��ϰ� �̹����� �������ִ� Ŭ�����Դϴ�.

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
