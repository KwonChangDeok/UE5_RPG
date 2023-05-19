// Character Ŭ������ ��ӹ޾� ��� ���Ͱ� �����ϴ� ��ɵ��� ������ Ŭ�����Դϴ�.

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
	// �������Ϳ� �Ϲݸ��Ͱ� �ٸ� ���� �������Ʈ�� �ش� �������� �ʱ�ȭ �Ͽ� �ٸ� UI�� ���� �� �ֵ��� �����ϰ��� �߽��ϴ�.
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

	// ���� �����Լ��� ������� ���� ������ �߻� Ŭ������ ����ԵǸ� �ν��Ͻ��� ������ �� ���� �ǹǷ�
	// �ٿ�ĳ������ Ȱ���ϱ� ��ư� �Ǳ� ������ �̷��� �����߽��ϴ�.
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
