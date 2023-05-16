// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "SkillSoundActor.generated.h"

UCLASS()
class ASSASSIN_API ASkillSoundActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillSoundActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
	USceneComponent* mRoot;

	FTimerHandle SoundTimer;

	FVector Location;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PlaySound();

	void SetLocation(FVector Loc)
	{
		Location = Loc;
	}

	void SetDelay(float Seconds)
	{
		GetWorld()->GetTimerManager().SetTimer(SoundTimer, this, &ASkillSoundActor::PlaySound, Seconds, false, -1.f);
	}
};
