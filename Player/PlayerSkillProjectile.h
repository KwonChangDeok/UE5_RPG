/*
Actor Ŭ������ ��ӹ޾� ������ �÷��̾��� ��ų ����ü Ŭ�����Դϴ�. ����ü�� ���¿� ������, �浹ó��, �Ҹ����� ���� �����߽��ϴ�.
*/

// �ش� Ŭ������ �����ϸ�, ����ü�� �浹ó���� ����� �̷������ �ʴ� ������ �޾����ϴ�.
// �̴� �� ������Ʈ�� ��Ʈ ������Ʈ�� �����Ͽ� �߻��� �������µ�, ������ �ذ������� ��ü���� ������ �ľ����� ���߽��ϴ�.
// �� �浹 ������ �� �� ���� ������Ʈ�� ��Ʈ������Ʈ�� ����������, ���������� ����(����ü�� ���� ���Ͱ� ���ư��� ���������ϴ�.)�� �ް� �Ǵ���
// �𸮾��� �� �ƴ� �پ ������ ���İ� ������ �ְ������ �˾Ƴ��� �ͽ��ϴ�.

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
