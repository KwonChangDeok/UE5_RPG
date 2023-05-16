// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components\TextBlock.h>

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "MonsterDamageBase.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API UMonsterDamageBase : public UUserWidget
{
	GENERATED_BODY()
private:
	UTextBlock* mDamage;
	float mPositionX;
	float mPositionY;

public:
	virtual void NativeConstruct() override;

public:
	void SetDamage(FText Damage);
	void SetCriticalDamage(FText Damage);
};
