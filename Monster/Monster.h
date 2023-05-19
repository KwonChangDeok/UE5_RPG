// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components/WidgetComponent.h>
#include "GameFramework/ProjectileMovementComponent.h"

#include "MonsterBase.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

UCLASS()
class ASSASSIN_API AMonster : public AMonsterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();
	FTimerHandle InitTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* AIController);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

public:
	virtual void Attack();

	void InitializeInfo();
};
