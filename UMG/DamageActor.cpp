// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageActor.h"
#include "MonsterDamageBase.h"

// Sets default values
ADamageActor::ADamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<UUserWidget> InfoFinder(_T("WidgetBlueprint'/Game/Blueprint/UMG/UMG_MonsterDamage.UMG_MonsterDamage_C'"));
	if (InfoFinder.Succeeded())
	{
		mMonsterDamageBaseClass = InfoFinder.Class;
		mWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(_T("Widget"));
		mWidgetComponent->SetWidgetClass(mMonsterDamageBaseClass);
	}

	mMonsterDamageBase = nullptr;
	CurZ = 0.f;
	key = false;
}

// Called when the game starts or when spawned
void ADamageActor::BeginPlay()
{
	Super::BeginPlay();
	
	mWidgetComponent->SetDrawSize(FVector2D(500.f, 200.f));
	mWidgetComponent->SetVisibility(true);
	mWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	mWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetWorldTimerManager().SetTimer(InitTimer, this, &ADamageActor::MakeInstance, 0.1f, true, -1.f);
}

// Called every frame
void ADamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurZ <= 1.f && key)
	{
		SetDamagePosition(DeltaTime);
	}

	if (IsValid(mMonsterDamageBase) && !mDamage.IsEmpty() && !key)
	{
		if (IsCritical)
		{
			mMonsterDamageBase->SetCriticalDamage(mDamage);
			key = true;
		}
		else
		{
			mMonsterDamageBase->SetDamage(mDamage);
			key = true;
		}
	}
}

void ADamageActor::SetDamage(FText Damage)
{
	mDamage = Damage;
	IsCritical = false;
}

void ADamageActor::SetCriticalDamage(FText Damage)
{
	mDamage = Damage;
	IsCritical = true;
}


void ADamageActor::SetDamagePosition(float DeltaTime)
{
	float InterpSpeed = 5.f;

	float NewZ = FMath::FInterpTo(CurZ, 1.f, DeltaTime, InterpSpeed);

	CurZ = NewZ;

	mWidgetComponent->AddRelativeLocation(FVector(0.f, 0.f, CurZ));
}

void ADamageActor::MakeInstance()
{
	if (!IsValid(mMonsterDamageBase))
	{
		mMonsterDamageBase = Cast<UMonsterDamageBase>(mWidgetComponent->GetWidget());
	}
	else
	{
		GetWorldTimerManager().ClearTimer(InitTimer);
	}
}



