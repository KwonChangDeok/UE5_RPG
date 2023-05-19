/*
GameModeBase Ŭ������ ��ӹ޾� ����UI ��ü �Ҵ� �� ����Ʈ �� Ŭ����, 
�÷��̾� ��Ʈ�ѷ� Ŭ������ �������ִ� ����� �߰��� �����մϴ�.
*/

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "AssassinGameModeBase.generated.h"

// ���Ӹ��� ���� �� �ϳ��� ����������, ���⼭ ������ ����UI�� �����ϰ� ����Ʈ�� �߰��ϵ��� �����߽��ϴ�.
// ���� ���Ŀ� �̴ϰ����� �߰��� ���� UI�� ����Ǿ�� �� �ʿ䰡 �ִٸ� �ش� ������ �ٸ� ���Ӹ�带 ����Ͽ� ���߿� ������ ���� ����� ���̶�
// �Ǵ��߽��ϴ�.

UCLASS()
class ASSASSIN_API AAssassinGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AAssassinGameModeBase();

private:
	TSubclassOf<UUserWidget> mMainUIClass;
	// ���� ������ �̿��� ������Ͽ����� Ÿ ������� Include�� �������ν�, ��ȯ������ �߻����� �ʵ��� �߽��ϴ�.
	class UMainUIBase* mMainUI;

public:
	virtual void BeginPlay()	override;

public:
	// Getter, Setter�Լ� �� ������ �Լ��� ������Ͽ� �����ߴµ�, �̴� ���� ������, ���� ���� �ۼ��ϵ��� �ϰڽ��ϴ�.
	UMainUIBase* GetMainUI()
	{
		return mMainUI;
	}
};
