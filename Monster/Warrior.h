// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Monster.h"
#include "Warrior.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API AWarrior : public AMonster
{
	GENERATED_BODY()
public:
	AWarrior();

public:
	virtual void Attack() override;
};
