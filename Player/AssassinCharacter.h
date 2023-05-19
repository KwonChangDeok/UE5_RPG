
/*
PlayerCharacter 클래스를 상속받아 생성자에서 다양한 메시들과 애니메이션 클래스를 로드 및 데이터테이블로 부터 값을 읽어오기 위한 
Assassin캐릭터의 RowName 값을 할당해주는 기능 등을 구현한 클래스입니다.
*/

// 추후 직업을 추가할 것을 고려해 PlayerCharacter에는 공통적인 기능을 정의하고 각각의 직업을 이를 상속받아 구현하려했으나,
// 개발 당시 공유할 수 없는 로직들을 PlayerCharacter에 작성하는 실수를 범했습니다.
// 이는 정확하지 않은 기획에 의한 실수였다고 생각하며 사전 클래스 설계의 중요성을 느낄 수 있었습니다.
#pragma once

#include "PlayerCharacter.h"
#include "AssassinCharacter.generated.h"

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
