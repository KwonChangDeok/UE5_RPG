// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "DecalBoundary.generated.h"

UCLASS()
class ASSASSIN_API ADecalBoundary : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADecalBoundary();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UDecalComponent* mDecal;

	FVector mLocation;

	bool mTickKey;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetDecalWorldLocation(FVector Location)
	{
		mLocation = Location;
		mTickKey = true;
	}
};
