// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BossMonster.h"
#include "Lich.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API ALich : public ABossMonster
{
	GENERATED_BODY()
public:
	ALich();

private:
	FTimerHandle Skill3Timer;

	USkeletalMesh* BerserkMesh;

	// ±¤ÆøÈ­ ½ÃÄö½º
	ULevelSequence* mBerserkSequence;
	FMovieSceneSequencePlaybackSettings	mBerserkSetting;

	ULevelSequencePlayer* mBerserkPlayer;
	ALevelSequenceActor* mBerserkActor;

	// ¾Æ¿ôÆ®·Î ½ÃÄö½º
	ULevelSequence* mDeathSequence;
	FMovieSceneSequencePlaybackSettings	mDeathSetting;

	ULevelSequencePlayer* mDeathPlayer;
	ALevelSequenceActor* mDeathActor;

	FTimerHandle ResurrectionTimer;
	
protected:
	virtual void PossessedBy(AController* AIController);

public:
	virtual void Attack() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

public:
	void Skill1Attack();

	void Skill2Attack();

	void Skill3Attack();

	void BerserkAttack(class APlayerCharacter* Target);

	void Resurrection();

	void Outro();

	UFUNCTION()
	void BerserkFinish();
};
