// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Monster.h"
#include "Ranger.generated.h"

/**
 * 
 */
UCLASS()
class ASSASSIN_API ARanger : public AMonster
{
	GENERATED_BODY()
public:
	ARanger();

public:
	virtual void Attack() override;
	
};
