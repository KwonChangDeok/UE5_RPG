// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxTriggerBase.h"

// Sets default values
ABoxTriggerBase::ABoxTriggerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(_T("Root"));

	SetRootComponent(mRoot);

	mRoot->SetVisibility(true);
}

// Called when the game starts or when spawned
void ABoxTriggerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoxTriggerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoxTriggerBase::OnConstruction(const FTransform& Transform)
{
	mBox = NewObject<UBoxComponent>(this, UBoxComponent::StaticClass(), _T("Box"));
	mBox->RegisterComponent();
	mBox->AttachToComponent(mRoot, FAttachmentTransformRules::KeepRelativeTransform);
	mBox->SetCollisionProfileName(_T("PlayerTrigger"));
	mBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	mBox->OnComponentBeginOverlap.AddDynamic(this, &ABoxTriggerBase::BeginOverlap);
	mBox->OnComponentEndOverlap.AddDynamic(this, &ABoxTriggerBase::EndOverlap);
}

void ABoxTriggerBase::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TriggerBegin(SweepResult);
}

void ABoxTriggerBase::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TriggerEnd();
}

void ABoxTriggerBase::TriggerBegin(const FHitResult& SweepResult)
{
}

void ABoxTriggerBase::TriggerEnd()
{
}
