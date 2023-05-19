// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Monster.h"
#include "Sentinel.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API ASentinel : public AMonster
{
	GENERATED_BODY()
public:
	ASentinel();

public:
	virtual void Attack() override;
};
