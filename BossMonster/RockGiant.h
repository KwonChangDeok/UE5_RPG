// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BossMonster.h"
#include "RockGiant.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API ARockGiant : public ABossMonster
{
	GENERATED_BODY()
public:
	ARockGiant();

private:
	ULevelSequence* mLevelSequence;
	FMovieSceneSequencePlaybackSettings	mSetting;

	ULevelSequencePlayer* mSequencePlayer;
	ALevelSequenceActor* mSequenceActor;

protected:
	virtual void PossessedBy(AController* AIController);

public:
	virtual void Attack() override;

	void Skill1Attack();

	void Skill2Hand();

	void Skill2Attack();

	void ThrowRock();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	void PlayOutro();
};
