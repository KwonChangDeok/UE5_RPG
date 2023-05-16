// Fill out your copyright notice in the Description page of Project Settings.


#include "Ranger.h"
#include "../Player/PlayerCharacter.h"

ARanger::ARanger()
{
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	mMonsterInfoRowName = _T("Ranger");
}

void ARanger::Attack()
{
	FVector MuzzleLoc = GetMesh()->GetSocketLocation(_T("Muzzle_Front"));

	FActorSpawnParameters	SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector	End = MuzzleLoc + GetActorForwardVector() * mMonsterInfo.AttackRange;

	FCollisionQueryParams	param(NAME_None, false, this);

	TArray<FHitResult> Result;
	bool Collision = GetWorld()->LineTraceMultiByChannel(Result, MuzzleLoc, End, ECollisionChannel::ECC_GameTraceChannel7, param);

	if (Collision)
	{
		int32 Count = Result.Num();

		for (int32 i = 0; i < Count; i++)
		{
			float Damage = mMonsterInfo.AttackPoint * FMath::FRandRange(0.8, 1.2);

			APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Result[i].GetActor());
			if (IsValid(PlayerCharacter))
			{
				PlayerCharacter->TakeDamage(Damage, FDamageEvent(), GetController(), this);
			}
		}
	}
}
