// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components\Image.h>

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "ClickedItemBase.generated.h"

/**
 * 
 */
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
