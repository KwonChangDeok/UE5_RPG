// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "AssassinGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API AAssassinGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AAssassinGameModeBase();

private:
	TSubclassOf<UUserWidget> mMainUIClass;
	class UMainUIBase* mMainUI;

public:
	virtual void BeginPlay()	override;

public:
	UMainUIBase* GetMainUI()
	{
		return mMainUI;
	}
};
