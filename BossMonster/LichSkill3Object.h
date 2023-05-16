// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "LichSkill3Object.generated.h"

UCLASS()
class ASSASSIN_API ALichSkill3Object : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALichSkill3Object();

private:
	FTimerHandle BoomTimer;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
	USceneComponent* mRoot;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void Boom();

};
