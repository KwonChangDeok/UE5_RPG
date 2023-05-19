// Character 클래스를 상속받아 모든 몬스터가 공유하는 기능들을 구현한 클래스입니다.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "MonsterBase.generated.h"

UCLASS()
class ASSASSIN_API AMonsterBase : public ACharacter
{
	GENERATED_BODY()
public:
	AMonsterBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FMonsterInfo mMonsterInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FName mMonsterInfoRowName;

	UPROPERTY()
	class AMonsterAIController* MonsterAIController;

protected:
	// 보스몬스터와 일반몬스터가 다른 위젯 블루프린트로 해당 변수들을 초기화 하여 다른 UI를 가질 수 있도록 구현하고자 했습니다.
	TSubclassOf<class UMonsterInfoBase> mMonsterInfoBaseClass;
	UWidgetComponent* mWidgetComponent;

	class UMonsterAnimInstance* mAnimInst;

	FTimerHandle InitTimer;

	TArray<FVector> mPatrolPointLocationArray;

	int32 mPatrolIndex;

	bool mPatrolEnable;

	bool mIsUltimate;

	float mPatrolWaitTime;

	bool mAttackEnable;

	bool mIsCritical;

	bool mBoss;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* AIController);

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

public:

	// 순수 가상함수를 사용하지 않은 이유는 추상 클래스를 만들게되면 인스턴스를 생성할 수 없게 되므로
	// 다운캐스팅을 활용하기 어렵게 되기 때문에 이렇게 구현했습니다.
	virtual void Attack();

	const FMonsterInfo& GetMonsterInfo() const
	{
		return mMonsterInfo;
	}

	UMonsterAnimInstance* GetAnimInstance()
	{
		return mAnimInst;
	}

	void SetPatrolLocation(TArray<FVector> PatrolPointLocationArray)
	{
		mPatrolPointLocationArray = PatrolPointLocationArray;
	}

	FVector GetPatrolLocation()
	{
		if (mPatrolPointLocationArray.Num() != 0)
		{
			return mPatrolPointLocationArray[mPatrolIndex];
		}
		return FVector::ZeroVector;
	}

	void AddPatrolIndex()
	{
		mPatrolIndex = (mPatrolIndex + 1) % mPatrolPointLocationArray.Num();
	}

	bool GetPatrolEnable()
	{
		return mPatrolEnable;
	}

	void SetPatrolEnable(bool PatrolEnable)
	{
		mPatrolEnable = PatrolEnable;
	}

	void SetIsUltimate(bool IsUltimate)
	{
		mIsUltimate = IsUltimate;
	}

	void AddPatrolWaitTime(float time)
	{
		mPatrolWaitTime += time;
	}

	float GetPatrolWaitTime()
	{
		return mPatrolWaitTime;
	}

	void ClearPatrolWaitTime()
	{
		mPatrolWaitTime = 0.f;
	}

	void SetAttackEnable(bool Value)
	{
		mAttackEnable = Value;
	}

	bool GetAttackEnable()
	{
		return mAttackEnable;
	}

	void SetCritical(bool IsCritical)
	{
		mIsCritical = IsCritical;
	}

};
