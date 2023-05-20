/*
BoxTriggerBase 클래스를 상속받아 바위거인 맵에서 오버랩시 인트로 시네마틱을 재생하도록 구현했으며, 
시네마틱 종료 후 플레이어와 보스를 적절한 위치로 이동시킵니다. 레벨시퀀스와 플레이백세팅을 에디터상에서 설정할 수 있도록 구현했습니다
*/

#pragma once

#include "BoxTriggerBase.h"
#include "RockGiantIntro.generated.h"

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
