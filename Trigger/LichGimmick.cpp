// Fill out your copyright notice in the Description page of Project Settings.


#include "LichGimmick.h"
#include "../Player/PlayerCharacter.h"
#include "../BossMonster/Lich.h"

ALichGimmick::ALichGimmick()
{
}

void ALichGimmick::TriggerBegin(const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	ALich* Boss = Cast<ALich>(UGameplayStatics::GetActorOfClass(GetWorld(), ALich::StaticClass()));

	if (IsValid(PlayerCharacter) && IsValid(Boss))
	{
		if (PlayerCharacter->GetPlayerInfo().HP == 1 && Boss->GetMonsterInfo().HP == 0)
		{
			Boss->Outro();
		}
	}
}
