// Fill out your copyright notice in the Description page of Project Settings.


#include "LichFire.h"
#include "../Player/PlayerCharacter.h"
#include "../AssassinGameModeBase.h"

ALichFire::ALichFire()
{
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(_T("ParticleSystemComponent"));
	ParticleSystemComponent->SetupAttachment(mRoot);
}

void ALichFire::Tick(float DeltaTime)
{
}

void ALichFire::TriggerBegin(const FHitResult& SweepResult)
{
	GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &ALichFire::Fire, 1.f, true, -1.f);
}

void ALichFire::TriggerEnd()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimer);
}

void ALichFire::Fire()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (IsValid(PlayerCharacter))
	{
		if (PlayerCharacter->GetPlayerInfo().HP > 1)
		{
			PlayerCharacter->GetPlayerInfo().HP -= 1;

			AAssassinGameModeBase* GameMode = Cast<AAssassinGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			GameMode->GetMainUI()->SetHP(PlayerCharacter->GetPlayerInfo().HP, PlayerCharacter->GetPlayerInfo().HPMax);
		}
	}
}
