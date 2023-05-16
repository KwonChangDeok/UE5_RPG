// Fill out your copyright notice in the Description page of Project Settings.


#include "Warrior.h"
#include "../Player/PlayerCharacter.h"

AWarrior::AWarrior()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(110.f);
	GetCapsuleComponent()->SetCapsuleRadius(50.f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -110.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	mMonsterInfoRowName = _T("Warrior");
}

void AWarrior::Attack()
{
	FVector StartLoc = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	FVector EndLoc = StartLoc + GetActorForwardVector() * mMonsterInfo.AttackRange;

	FCollisionQueryParams param(NAME_None, false, this);
	TArray<FHitResult> Result;

	FQuat CapsuleRotation = FRotator(0.f, 90.f, 0.f).Quaternion();

	bool Collision = GetWorld()->SweepMultiByChannel(Result, StartLoc, EndLoc, CapsuleRotation,
		ECollisionChannel::ECC_GameTraceChannel7, FCollisionShape::MakeSphere(50.f), param);

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
