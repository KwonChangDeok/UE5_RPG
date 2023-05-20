// BossMonster 클래스를 상속받아 바위거인의 기본 공격 및 스킬, 기믹 등을 구현한 클래스입니다.

#pragma once

#include "BossMonster.h"
#include "RockGiant.generated.h"

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
