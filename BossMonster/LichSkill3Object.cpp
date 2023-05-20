#include "LichSkill3Object.h"
#include "../Player/PlayerCharacter.h"
#include "../AssassinGameModeBase.h"
#include "Lich.h"

ALichSkill3Object::ALichSkill3Object()
{
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(_T("RootComponent"));
	mRoot->SetVisibility(true);

	SetRootComponent(mRoot);
}

void ALichSkill3Object::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(BoomTimer, this, &ALichSkill3Object::Boom, 0.5f, false, -1.f);
}

void ALichSkill3Object::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALichSkill3Object::Boom()
{
	FVector StartLoc = GetActorLocation();
	FVector EndLoc = GetActorLocation();

	FCollisionQueryParams param(NAME_None, false, this);
	TArray<FHitResult> Result;

	bool Collision = GetWorld()->SweepMultiByChannel(Result, StartLoc, EndLoc, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel7, FCollisionShape::MakeSphere(100.f), param);

	if (Collision)
	{
		int32 Count = Result.Num();

		for (int32 i = 0; i < Count; i++)
		{
			APlayerCharacter* Player = Cast<APlayerCharacter>(Result[i].GetActor());
			ALich* Boss = Cast<ALich>(UGameplayStatics::GetActorOfClass(GetWorld(), ALich::StaticClass()));

			if (IsValid(Player) && IsValid(Boss))
			{
				float Damage = 300.f;

				Boss->SkillDamage(Damage, Player);
			}
		}
	}

	Destroy();
}

