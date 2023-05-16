// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components/WidgetComponent.h>

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "DamageActor.generated.h"

UCLASS()
class ASSASSIN_API ADamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageActor();

private:
	TSubclassOf<class UMonsterDamageBase> mMonsterDamageBaseClass;
	UWidgetComponent* mWidgetComponent;

	float CurZ;
	bool key;

	FTimerHandle InitTimer;

	FText mDamage;
	bool IsCritical;

	class UMonsterDamageBase* mMonsterDamageBase;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetDamage(FText Damage);
	void SetCriticalDamage(FText Damage);
	void SetDamagePosition(float DeltaTime);

	void MakeInstance();
};
