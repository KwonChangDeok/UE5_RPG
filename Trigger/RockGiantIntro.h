/*
BoxTriggerBase Ŭ������ ��ӹ޾� �������� �ʿ��� �������� ��Ʈ�� �ó׸�ƽ�� ����ϵ��� ����������, 
�ó׸�ƽ ���� �� �÷��̾�� ������ ������ ��ġ�� �̵���ŵ�ϴ�. ������������ �÷��̹鼼���� �����ͻ󿡼� ������ �� �ֵ��� �����߽��ϴ�
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
