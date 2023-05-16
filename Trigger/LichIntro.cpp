// Fill out your copyright notice in the Description page of Project Settings.


#include "LichIntro.h"
#include "../Player/PlayerCharacter.h"
#include "../BossMonster/Lich.h"

ALichIntro::ALichIntro()
{
	mSequencePlayer = nullptr;
	mSequenceActor = nullptr;
}

void ALichIntro::TriggerBegin(const FHitResult& SweepResult)
{
	if (IsValid(mLevelSequence))
	{
		if (!mSequencePlayer)
		{
			mSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
				GetWorld(), mLevelSequence, mSetting, mSequenceActor);
		}

		mSequencePlayer->Play();

		mSequencePlayer->OnFinished.AddDynamic(this, &ALichIntro::SequenceFinish);
	}
}

void ALichIntro::SequenceFinish()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ALich* Boss = ALich::StaticClass()->GetDefaultObject<ALich>();

	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->SetActorLocation(FVector(-178.f, -1785.f, 88.000031f));
	}

	if (IsValid(Boss))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<ALich>(Boss->GetClass(), FVector(1088.f, -1781.f, 201.740312f), FRotator(0.f, 180.f, 0.f), SpawnParams);
	}
}
