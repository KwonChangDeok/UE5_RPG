// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnPoint.h"
#include "MonsterBase.h"
#include "MonsterPatrolPoint.h"

// Sets default values
AMonsterSpawnPoint::AMonsterSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(_T("Root"));
	SetRootComponent(mRoot);

	mRoot->SetVisibility(true);

	mMonsterRespawnTime = 10.f;
}

// Called when the game starts or when spawned
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

// Called every frame
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

