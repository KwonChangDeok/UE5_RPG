#include "MonsterPatrolPoint.h"

AMonsterPatrolPoint::AMonsterPatrolPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	// ���� Ÿ���ν� ���� ���� _T�� ����ϴ� ���Դϴ�. �̴� ���� �����鿡�� ����� �ϴ� �κ��̶�� �����մϴ�.
	// ����, �Ʒ��� ���� ���ڸ������� �ڵ��ϼ� ����� �̿��� �ϰ������� _T�� TEXT�� ȥ���ϴ� �Ǽ��� ���ߴµ�
	// ������ �̷��� ���� ����ؾ߰ڴٴ� ���� �������ϴ�.
	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(mRoot);

	mRoot->SetVisibility(true);
}

void AMonsterPatrolPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMonsterPatrolPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

