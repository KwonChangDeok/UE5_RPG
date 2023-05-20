// BoxTriggerBase Ŭ������ ��ӹ޾� ��ġ �ʿ��� �������� ��Ʈ�� �ó׸�ƽ�� ����ϵ��� ����������, '
// �ó׸�ƽ ���� �� �÷��̾�� ������ ������ ��ġ�� �̵���ŵ�ϴ�.

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