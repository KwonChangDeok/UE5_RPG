// ABossMonster 클래스를 상속받아 리치의 기본공격 및 스킬, 기믹을 구현한 클래스입니다.

#pragma once

#include "BossMonster.h"
#include "Lich.generated.h"

UCLASS()
class ASSASSIN_API ALich : public ABossMonster
{
	GENERATED_BODY()
public:
	ALich();

private:
	FTimerHandle Skill3Timer;

	USkeletalMesh* BerserkMesh;

	// 광폭화 시퀀스
	ULevelSequence* mBerserkSequence;
	FMovieSceneSequencePlaybackSettings	mBerserkSetting;

	ULevelSequencePlayer* mBerserkPlayer;
	ALevelSequenceActor* mBerserkActor;

	// 아웃트로 시퀀스
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
