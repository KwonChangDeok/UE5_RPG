// BoxTriggerBase 클래스를 상속받아 리치 맵에서 오버랩시 인트로 시네마틱을 재생하도록 구현했으며, '
// 시네마틱 종료 후 플레이어와 보스를 적절한 위치로 이동시킵니다.

#pragma once

#include "BoxTriggerBase.h"
#include "LichIntro.generated.h"

UCLASS()
class ASSASSIN_API ALichIntro : public ABoxTriggerBase
{
	GENERATED_BODY()
public:
	ALichIntro();

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