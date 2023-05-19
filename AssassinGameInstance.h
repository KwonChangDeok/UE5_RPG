/*
 GameInstance Ŭ������ ��ӹ޾� �����ڿ��� �پ��� ������ ���̺��� �ε��ϰ�,
 �ش� ���̺��� Ư�� �����͸� �˻��ϴ� ����� �����մϴ�.
 �� ������ ���̺��� ���ӿ��� ���Ǵ� �÷��̾� ����, ���� ����, ������ ���� ���� ��� �ֽ��ϴ�.
*/
#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "AssassinGameInstance.generated.h"

// ���������̺��� �ε�� ���ӿ��尡 ������ ���� �����̿��� �ϰ�,
// ������ ���� �� �ε��ܰԿ��� ���������̺��� �ε��ϴ°��� �ùٸ��� �����Ͽ�
// �����ν��Ͻ��� �����ڿ��� �̸� �����ϵ��� �����߽��ϴ�.

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
