// Fill out your copyright notice in the Description page of Project Settings.


#include "RockGiantIntro.h"
#include "../Player/PlayerCharacter.h"
#include "../BossMonster/RockGiant.h"

ARockGiantIntro::ARockGiantIntro()
{
	mSequencePlayer = nullptr;
	mSequenceActor = nullptr;
}

void ARockGiantIntro::TriggerBegin(const FHitResult& SweepResult)
{
	if (IsValid(mLevelSequence))
	{
		if (!mSequencePlayer)
		{
			mSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
				GetWorld(), mLevelSequence, mSetting, mSequenceActor);
		}

		mSequencePlayer->Play();

		mSequencePlayer->OnFinished.AddDynamic(this, &ARockGiantIntro::SequenceFinish);
	}
}

void ARockGiantIntro::SequenceFinish()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	ARockGiant* Boss = ARockGiant::StaticClass()->GetDefaultObject<ARockGiant>();

	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->SetActorLocation(FVector(-1850.f, 0.f, 108.f));
	}

	if (IsValid(Boss))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<ARockGiant>(Boss->GetClass(), FVector(1360.f, -30.f, 195.04322f), FRotator(0.f, 180.f, 0.f), SpawnParams);
	}

}
