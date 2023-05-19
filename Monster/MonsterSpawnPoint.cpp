#include "MonsterSpawnPoint.h"
#include "MonsterBase.h"
#include "MonsterPatrolPoint.h"

AMonsterSpawnPoint::AMonsterSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(_T("Root"));
	SetRootComponent(mRoot);

	// ���� ��Ű¡ �� SetVisibility �Լ� ��� bVisibility������Ƽ�� ���� �����ϴ� ���� ������ �Ǿ� ��Ű¡���� Unkwon Error�� �޾����ϴ�.
	// ��� �ڵ带 õõ�� ���캸�� �� ����ڵ尡 �߻��� Ŭ�������� ���������� bVisibility�� �����ߴٴ� ���� �߰��� �̸� �ذ��� �� �־����ϴ�.
	// �̷��� ������ ������ ���� ���� ���� ��ɸ��� �����ϴ� ���� �󸶳� ������ �� �ִ��� �������ϴ�.
	// ���� ������Ʈ�� �ƴ� �� ������Ʈ���ٸ�, �� ���ư� ȸ�� �������ٸ� ����� �����ϸ� ������ ����� ��Ⱑ �Ǿ����ϴ�.
	mRoot->SetVisibility(true);

	mMonsterRespawnTime = 10.f;
}

void AMonsterSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	mAccDelta = 0.f;

	for (int32 i = 0; i < mMonsterPatrolPoint.Num(); i++)
	{
		mMonsterPatolPointLocation.Add(mMonsterPatrolPoint[i]->GetActorLocation());
	}

	if (IsValid(mSpawnMonsterClass))
	{
		FActorSpawnParameters SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		SpawnMonster = GetWorld()->
			SpawnActor<AMonsterBase>(mSpawnMonsterClass, GetActorLocation(), GetActorRotation(), SpawnParam);
		SpawnMonster->SetPatrolLocation(mMonsterPatolPointLocation);
	}
}

void AMonsterSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(SpawnMonster))
	{
		return;
	}

	mAccDelta += DeltaTime;

	if (mAccDelta > mMonsterRespawnTime)
	{
		FActorSpawnParameters SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		SpawnMonster = GetWorld()->
			SpawnActor<AMonsterBase>(mSpawnMonsterClass, GetActorLocation(), GetActorRotation(), SpawnParam);
		SpawnMonster->SetPatrolLocation(mMonsterPatolPointLocation);

		mAccDelta = 0.f;
	}
}

