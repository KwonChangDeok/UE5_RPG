// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerCharacter.h"
#include "AssassinCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API AAssassinCharacter : public APlayerCharacter
{
	GENERATED_BODY()
public:
	AAssassinCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	UStaticMeshComponent* mWeapon_l;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	UStaticMeshComponent* mWeapon_r;

protected:
	USkeletalMesh* mShadowMesh;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	virtual void AttackSingle() override;
	virtual void AttackSpinning() override;
	virtual void AttackTwin() override;
	virtual void AttackFinish() override;
	virtual void SkillZApply() override;
	virtual void SkillZFinish() override;
	virtual void SkillXApply() override;
	virtual void SkillCApply() override;
	virtual void SkillVTeleport() override;
	virtual void SkillVApply() override;

public:
	void MakeParticle(FVector ImpactPoint);
};
