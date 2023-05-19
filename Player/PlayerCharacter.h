// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../UMG/MainUIBase.h"
#include <Components/WidgetComponent.h>

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ASSASSIN_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Component, meta = (AllowPrivateAccess = true))
	USpringArmComponent* mSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Component, meta = (AllowPrivateAccess = true))
	UCameraComponent* mCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FPlayerInfo	mPlayerInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FName mPlayerInfoRowName;

protected:
	// 정면, 후면 방향의 이동을 저장하기 위한 변수
	float mForwardScale;

	bool mDeath;

	class UPlayerAnimInstance* mAnimInst;

	class AMonsterBase* mSkillZTargetMonster;

	FVector mSkillXComeBackLocation;

	class AShadow* mShadow;

	class ADecal* Decal;
	class ADecalBoundary* DecalBoundary;

	// 대쉬중인지 판단하는것에 사용할 변수
	bool mDash;

	bool mPressedV;

	FTimerHandle PlayerInfoTimer;

	bool TargetArmKey;

	float OrgLength;
	float DestLength;

	FVector UltimateLocation;

	// 스킬 타이머 핸들러
	FTimerHandle DashTimer;
	FTimerHandle SkillZTimer;
	FTimerHandle SkillXTimer;
	FTimerHandle SkillCTimer;
	FTimerHandle SkillVTimer;

	FTimerHandle ResurrectionTimer;

	// 스킬 사용가능 여부
	bool mDashEnable;
	bool mSkillZFirstEnable;
	bool mSkillZSecondEnable;
	bool mSkillXFirstEnable;
	bool mSkillXSecondEnable;
	bool mSkillCEnable;
	bool mSkillVEnable;

	UMainUIBase* mMainUI;

	const float SkillZCoolTime = 10.f;
	const float SkillXCoolTime = 10.f;
	const float SkillCCoolTime = 10.f;
	const float SkillVCoolTime = 10.f;
	const float DashCoolTime = 5.f;

	float SkillZAcc;
	float SkillXAcc;
	float SkillCAcc;
	float SkillVAcc;
	float DashAcc;

	TSubclassOf<class UInventoryBase> mInventoryBaseClass;
	UWidgetComponent* mWidgetComponent;

	FTimerHandle InitTimer;

	TArray<FItemDataInfo> ItemArray;

	int32 mItemIndex;

	class UItemObject* mDragItem;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

public:
	// 축매핑
	// 앞, 뒤 이동
	void MoveForward(float scale);
	// 좌, 우 이동
	void MoveSide(float scale);

	// 액션매핑
	// 점프
	void SpaceBar();
	// 공격
	void Attack();
	// 대쉬
	void Dash();
	// Z스킬
	void SkillZ();
	// X스킬
	void SkillX();
	// C스킬
	void SkillC();
	// V스킬
	void SkillV();
	// 180도 회전
	void Turn();
	// 인벤토리
	void Inventory();
	// 인벤토리 마우스 버튼 업 이벤트
	void BtnUpEvent();
	// 퀵슬롯 아이템 소비
	void QuickSlot1();
	void QuickSlot2();
	void QuickSlot3();
	void QuickSlot4();

public:
	void SetSpringArmRotation(float RotationAccumulator)
	{
		mSpringArm->AddWorldRotation(FRotator(0.f, RotationAccumulator, 0.f));
	}

	FPlayerInfo& GetPlayerInfo()
	{
		return mPlayerInfo;
	}

	void GetSpecialPoint(int32 SpecialPoint)
	{
		if (mPlayerInfo.SpecialPoint + SpecialPoint >= 100)
		{
			mPlayerInfo.SpecialPoint = 100;
			return;
		}

		mPlayerInfo.SpecialPoint += SpecialPoint;
	}

	void SetPlayerInfoFromTime()
	{
		// SP 자연 감소
		if (mPlayerInfo.SpecialPoint - 10 <= 0)
		{
			mPlayerInfo.SpecialPoint = 0;
		}
		else if(!mPressedV)
		{
			mPlayerInfo.SpecialPoint -= 10;
		}

		// MP 자연 회복
		if (mPlayerInfo.MP + 100 >= mPlayerInfo.MPMax)
		{
			mPlayerInfo.MP = mPlayerInfo.MPMax;
		}
		else
		{
			mPlayerInfo.MP += 100;
		}

		mMainUI->SetMP(mPlayerInfo.MP, mPlayerInfo.MPMax);
		mMainUI->SetSP(mPlayerInfo.SpecialPoint / 100.f);
	}

	void SetDash(bool Dash)
	{
		mDash = Dash;
	}

	void SetDashEnable()
	{
		mDashEnable = true;
	}

	void SetSkillZFirstEnable()
	{
		mSkillZFirstEnable = true;
		mSkillZSecondEnable = false;
	}

	void SetSkillZSecondEnable(class AMonsterBase* Monster)
	{
		mSkillZSecondEnable = true;
		
		mSkillZTargetMonster = Monster;
	}

	void SetSkillXFirstEnable();

	void SetSkillXSecondEnable()
	{
		mSkillXSecondEnable = true;
	}

	void SetSkillCEnable()
	{
		mSkillCEnable = true;
	}

	void SetSkillVEnable()
	{
		mSkillVEnable = true;
	}

	UPlayerAnimInstance* GetAnimInst()
	{
		return mAnimInst;
	}

	EITEM_ID ConvertFromFNameToItemEnum(const FName& Name)
	{
		static const UEnum* EnumPtr = StaticEnum<EITEM_ID>();

		return static_cast<EITEM_ID>(EnumPtr->GetValueByName(Name));
	}

	void InitializeInven();

	void AddItem(FName ItemID);

	void AddGold(int32 Value);

	void SetTargetArmLength(float DeltaTime);
	
	void FootStep(bool Left);

	void SetDragItem(class UItemObject* DragItem);

	class UItemObject* GetDragItem()
	{
		return mDragItem;
	}

	void TossItem();

	void Resurrection()
	{
		mDeath = false;
		mPlayerInfo.HP = mPlayerInfo.HPMax;
		mMainUI->SetHP(mPlayerInfo.HP, mPlayerInfo.HPMax);
	}

	virtual void AttackSingle() {}
	virtual void AttackSpinning() {}
	virtual void AttackTwin() {}
	virtual void AttackFinish() {}
	virtual void SkillZApply() {}
	virtual void SkillZFinish() {}
	virtual void SkillXApply() {}
	virtual void SkillCApply() {}
	virtual void SkillVTeleport() {}
	virtual void SkillVApply() {}
	virtual void MakeParticle(FVector ImpactPoint) {}
};
