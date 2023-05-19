/*
 GameInstance 클래스를 상속받아 생성자에서 다양한 데이터 테이블을 로드하고,
 해당 테이블에서 특정 데이터를 검색하는 기능을 수행합니다.
 각 데이터 테이블은 게임에서 사용되는 플레이어 정보, 몬스터 정보, 아이템 정보 등을 담고 있습니다.
*/
#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "AssassinGameInstance.generated.h"

// 데이터테이블의 로드는 게임월드가 생성된 이후 시점이여야 하고,
// 게임의 시작 전 로딩단게에서 데이터테이블을 로드하는것이 올바르다 생각하여
// 게임인스턴스의 생성자에서 이를 수행하도록 구현했습니다.

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
