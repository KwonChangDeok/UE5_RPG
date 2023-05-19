// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "AssassinGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API UAssassinGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UAssassinGameInstance();

private:
	UDataTable* mPlayerInfoTable;
	UDataTable* mMonsterInfoTable;
	UDataTable* mItemInfoTable;

public:
	const FPlayerTableInfo* GetPlayerTable(const FName& RowName);
	const FMonsterTableInfo* GetMonsterTable(const FName& RowName);
	const FItemDataInfo* GetItemTable(const FName& RowName);
};
