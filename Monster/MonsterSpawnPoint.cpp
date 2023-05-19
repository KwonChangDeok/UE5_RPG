#include "MonsterSpawnPoint.h"
#include "MonsterBase.h"
#include "MonsterPatrolPoint.h"

AMonsterSpawnPoint::AMonsterSpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(_T("Root"));
	SetRootComponent(mRoot);

	// 게임 패키징 시 SetVisibility 함수 대신 bVisibility프로퍼티에 직접 접근하는 것이 문제가 되어 패키징에서 Unkwon Error를 겪었습니다.
	// 경고 코드를 천천히 살펴보던 중 경고코드가 발생한 클래스들이 공통적으로 bVisibility를 수정했다는 것을 발견해 이를 해결할 수 있었습니다.
	// 이러한 문제를 겪으며 깊은 이해 없이 기능만을 구현하는 것이 얼마나 위험할 수 있는지 느꼈습니다.
	// 개인 프로젝트가 아닌 팀 프로젝트였다면, 더 나아가 회사 업무였다면 어땠을지 생각하며 마음을 다잡는 계기가 되었습니다.
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

