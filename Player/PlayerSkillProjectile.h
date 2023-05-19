/*
Actor 클래스를 상속받아 구현한 플레이어의 스킬 투사체 클래스입니다. 투사체의 형태와 움직임, 충돌처리, 소멸조건 등을 정의했습니다.
*/

// 해당 클래스를 구현하며, 투사체의 충돌처리가 제대로 이루어지지 않는 문제를 겪었습니다.
// 이는 신 컴포넌트를 루트 컴포넌트로 지정하여 발생한 문제였는데, 문제는 해결했지만 구체적인 원인은 파악하지 못했습니다.
// 왜 충돌 판정을 할 수 없는 컴포넌트를 루트컴포넌트로 지정했을때, 비정상적인 문제(투사체에 맞은 몬스터가 날아가는 문제였습니다.)를 겪게 되는지
// 언리얼을 잘 아는 뛰어난 동료들과 지식과 경험을 주고받으며 알아내고 싶습니다.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "PlayerSkillProjectile.generated.h"

UCLASS()
class ASSASSIN_API APlayerSkillProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerSkillProjectile();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	UStaticMeshComponent* StaticMeshComponent;

	float SkillDamage;

	float SkillRange;

	float AccDistance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSkillDamage(float Damage)
	{
		SkillDamage = Damage;
	}

	void SetStaticMesh(UStaticMesh* Mesh)
	{
		StaticMeshComponent->SetStaticMesh(Mesh);
	}

	void SetSkillRange(float Range)
	{
		SkillRange = Range;
	}

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
