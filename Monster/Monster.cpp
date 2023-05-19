// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "../AssassinGameInstance.h"
#include "MonsterAnimInstance.h"
#include "AI/MonsterAIController.h"
#include "../UMG/MonsterInfoBase.h"
#include "../UMG/DamageActor.h"
#include "../Player/PlayerCharacter.h"
#include "../AssassinGameModeBase.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<UUserWidget> InfoFinder(TEXT("WidgetBlueprint'/Game/Blueprint/UMG/UMG_MonsterInfo.UMG_MonsterInfo_C'"));
	if (InfoFinder.Succeeded())
	{
		mMonsterInfoBaseClass = InfoFinder.Class;
		mWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(_T("Widget"));
		mWidgetComponent->SetupAttachment(GetMesh());
		mWidgetComponent->SetWidgetClass(mMonsterInfoBaseClass);
	}

	mBoss = false;
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

	mWidgetComponent->SetDrawSize(FVector2D(500.f, 500.f));
	mWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	mWidgetComponent->SetVisibility(true);
	mWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	mWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetWorldTimerManager().SetTimer(InitTimer, this, &AMonster::InitializeInfo, 0.1f, false, -1.f);
}

void AMonster::PossessedBy(AController* AIController)
{
	Super::PossessedBy(AIController);
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return 0.f;
}

void AMonster::Attack()
{
}

void AMonster::InitializeInfo()
{
	UMonsterInfoBase* mMonsterInfoBase = Cast<UMonsterInfoBase>(mWidgetComponent->GetWidget());
	if (IsValid(mMonsterInfoBase))
	{
		mMonsterInfoBase->SetHP(mMonsterInfo.HP / (float)mMonsterInfo.HPMax);
		mMonsterInfoBase->SetName((FText::FromName(mMonsterInfo.Name)));
	}
}

