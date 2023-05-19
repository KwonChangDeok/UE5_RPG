#include "MonsterPatrolPoint.h"

AMonsterPatrolPoint::AMonsterPatrolPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	// 보통 타이핑시 편리를 위해 _T를 사용하는 편입니다. 이는 추후 팀원들에게 맞춰야 하는 부분이라고 생각합니다.
	// 또한, 아래와 같이 인텔리센스의 자동완성 기능을 이용해 일관성없이 _T와 TEXT를 혼용하는 실수를 범했는데
	// 앞으로 이러한 것을 경계해야겠다는 것을 느꼈습니다.
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

