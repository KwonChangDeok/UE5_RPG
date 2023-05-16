// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BoxTriggerBase.h"
#include "RockGiantIntro.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API ARockGiantIntro : public ABoxTriggerBase
{
	GENERATED_BODY()
public:
	ARockGiantIntro();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	ULevelSequence* mLevelSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FMovieSceneSequencePlaybackSettings	mSetting;

	ULevelSequencePlayer* mSequencePlayer;
	ALevelSequenceActor* mSequenceActor;

public:
	virtual void TriggerBegin(const FHitResult& SweepResult);

public:
	UFUNCTION()
	void SequenceFinish();
};
