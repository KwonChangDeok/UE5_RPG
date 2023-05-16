// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components\ProgressBar.h>
#include <Components\TextBlock.h>

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "MonsterInfoBase.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API UMonsterInfoBase : public UUserWidget
{
	GENERATED_BODY()
private:
	UProgressBar* mHPBar;
	UTextBlock* mName;
	UTextBlock* mHPText;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime);

public:
	void SetHP(float HPRatio);
	void SetName(FText Name);
	void SetText(FText Text);
};
