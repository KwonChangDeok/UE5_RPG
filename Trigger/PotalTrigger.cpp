// Fill out your copyright notice in the Description page of Project Settings.


#include "PotalTrigger.h"

APotalTrigger::APotalTrigger()
{
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(_T("ParticleSystemComponent"));
	ParticleSystemComponent->SetupAttachment(mRoot);
}

void APotalTrigger::TriggerBegin(const FHitResult& SweepResult)
{
	UGameplayStatics::OpenLevel(GetWorld(), mLevelName);
}
