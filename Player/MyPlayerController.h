// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerController();

private:
	float RotationAccumulator;
	class APlayerCharacter* PlayerCharacter;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
