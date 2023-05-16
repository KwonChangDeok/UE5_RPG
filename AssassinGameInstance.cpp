// Fill out your copyright notice in the Description page of Project Settings.


#include "AssassinGameInstance.h"

UAssassinGameInstance::UAssassinGameInstance() : mPlayerInfoTable(nullptr)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> PlayerInfoTable(_T("DataTable'/Game/Player/PlayerTable.PlayerTable'"));
	
	if (PlayerInfoTable.Succeeded())
	{
		mPlayerInfoTable = PlayerInfoTable.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterInfoTable(_T("DataTable'/Game/Monster/MonsterTable.MonsterTable'"));

	if (MonsterInfoTable.Succeeded())
	{
		mMonsterInfoTable = MonsterInfoTable.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> ItemInfoTable(_T("DataTable'/Game/Item/ItemDataTable.ItemDataTable'"));

	if (ItemInfoTable.Succeeded())
	{
		mItemInfoTable = ItemInfoTable.Object;
	}
}

const FPlayerTableInfo* UAssassinGameInstance::GetPlayerTable(const FName& RowName)
{
	return mPlayerInfoTable->FindRow<FPlayerTableInfo>(RowName, TEXT(""));
}

const FMonsterTableInfo* UAssassinGameInstance::GetMonsterTable(const FName& RowName)
{
	return mMonsterInfoTable->FindRow<FMonsterTableInfo>(RowName, TEXT(""));
}

const FItemDataInfo* UAssassinGameInstance::GetItemTable(const FName& RowName)
{
	return mItemInfoTable->FindRow<FItemDataInfo>(RowName, TEXT(""));
}
