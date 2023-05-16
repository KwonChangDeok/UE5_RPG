// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BoxTriggerBase.h"
#include "LichGimmick.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API ALichGimmick : public ABoxTriggerBase
{
	GENERATED_BODY()
public:
	ALichGimmick();

public:
	virtual void TriggerBegin(const FHitResult& SweepResult);
};
