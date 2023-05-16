// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillSoundActor.h"

// Sets default values
ASkillSoundActor::ASkillSoundActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(_T("RootComponent"));
	mRoot->SetVisibility(true);

	SetRootComponent(mRoot);
}

// Called when the game starts or when spawned
void ASkillSoundActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASkillSoundActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkillSoundActor::PlaySound()
{
	USoundWave* Sound = LoadObject<USoundWave>(nullptr, _T("SoundWave'/Game/Collections/RockGiantBoom2.RockGiantBoom2'"));

	if (IsValid(Sound))
	{
		UGameplayStatics::PlaySound2D(this, Sound);
	}
	
	UParticleSystem* ParticleSystem = LoadObject<UParticleSystem>(nullptr, _T("ParticleSystem'/Game/ParagonRampage/FX/Particles/Abilities/RipNToss/FX/P_Rampage_Rock_HitWorld.P_Rampage_Rock_HitWorld'"));
	UParticleSystemComponent* ParticleSystemComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, Location, FRotator::ZeroRotator);
}

