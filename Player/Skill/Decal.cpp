// Fill out your copyright notice in the Description page of Project Settings.


#include "Decal.h"

// Sets default values
ADecal::ADecal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mDecal = CreateDefaultSubobject<UDecalComponent>(_T("Decal"));

	SetRootComponent(mDecal);
	mDecal->SetVisibility(true);

	mLocation = FVector::ZeroVector;
	mTickKey = false;

	mDecal->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Mtrl(_T("Material'/Game/Collections/MTDecal.MTDecal'"));
	if (Mtrl.Succeeded())
	{
		mDecal->SetDecalMaterial(Mtrl.Object);
	}
}

// Called when the game starts or when spawned
void ADecal::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mTickKey)
	{
		mDecal->SetWorldLocation(mLocation);
		mTickKey = false;
	}
}

