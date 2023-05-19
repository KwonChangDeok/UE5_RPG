/*
Actor 클래스를 상속받아 바위거인의 바위 투사체를 구현한 클래스입니다.
바위의 낙하지점을 예상하여 데칼로 표현해주는 기능을 포함합니다.
*/

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "BossSkillPojectile.generated.h"

UCLASS()
class ASSASSIN_API ABossSkillPojectile : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ABossSkillPojectile();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	UStaticMeshComponent* StaticMeshComponent;

	class ADecal* Decal;

	float AccDelta;

	FVector HitLoc;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetStaticMesh(UStaticMesh* Mesh)
	{
		StaticMeshComponent->SetStaticMesh(Mesh);
	}

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
