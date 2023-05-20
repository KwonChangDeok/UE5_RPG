#include "BossMonster.h"
#include "../Player/PlayerCharacter.h"
#include "../Player/PlayerAnimInstance.h"
#include "../AssassinGameModeBase.h"
#include "../UMG/MonsterInfoBase.h"

ABossMonster::ABossMonster()
{
	mBoss = true;

	mWaitEnable = true;

	mSkillEnable = true;

	mIsBerserk = false;

	ConstructorHelpers::FClassFinder<UUserWidget> InfoFinder(_T("WidgetBlueprint'/Game/Blueprint/UMG/UMG_BossInfo.UMG_BossInfo_C'"));
	if (InfoFinder.Succeeded())
	{
		mMonsterInfoBaseClass = InfoFinder.Class;
		mWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(_T("Widget"));
		mWidgetComponent->SetWidgetClass(mMonsterInfoBaseClass);
	}

	BossSkillCoolTime = 10.f;
	BossWaitTime = 10.f;
}

void ABossMonster::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(WaitTimer, this, &ABossMonster::SetWaitTime, BossWaitTime, true, -1.f);

	GetWorldTimerManager().SetTimer(SkillTimer, this, &ABossMonster::SetSkillEnable, BossSkillCoolTime, true, -1.f);

	if (IsValid(mWidgetComponent))
	{
		mWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		// 고정된 값이 아닌, 현재 뷰포트 크기에 따른 비율로 설정하는 것이 적합하다고 생각합니다.
		mWidgetComponent->SetDrawSize(FVector2D(1000.0, 100.0));
		mWidgetComponent->GetUserWidgetObject()->AddToViewport();
		mWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		mWidgetComponent->SetVisibility(false);
	}

	GetWorldTimerManager().SetTimer(InitTimer, this, &ABossMonster::InitializeInfo, 0.1f, false, -1.f);
}

float ABossMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return 0.f;
}

void ABossMonster::SkillDamage(float DamageAmount, APlayerCharacter* DamagedPlayer)
{
	float Damage = (DamageAmount - DamagedPlayer->GetPlayerInfo().ArmorPoint) > 1.f ? (DamageAmount - DamagedPlayer->GetPlayerInfo().ArmorPoint) : 1.f;
	DamagedPlayer->GetPlayerInfo().HP -= Damage;

	if (DamagedPlayer->GetPlayerInfo().HP < 0)
	{
		DamagedPlayer->GetPlayerInfo().HP = 1;
		DamagedPlayer->TakeDamage(1.f, FDamageEvent(), GetController(), this);
	}

	AAssassinGameModeBase* GameMode = Cast<AAssassinGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->GetMainUI()->SetHP(DamagedPlayer->GetPlayerInfo().HP, DamagedPlayer->GetPlayerInfo().HPMax);

	// 구현 이후 영상을 편집하며 넉다운이 아닌 넉업이 더 적합한 표현일 것 이라고 생각했습니다.
	DamagedPlayer->GetAnimInst()->KnockDown();
}

void ABossMonster::InitializeInfo()
{
	UMonsterInfoBase* mMonsterInfoBase = Cast<UMonsterInfoBase>(mWidgetComponent->GetWidget());
	if (IsValid(mMonsterInfoBase))
	{
		mMonsterInfoBase->SetHP(mMonsterInfo.HP / (float)mMonsterInfo.HPMax);
		mMonsterInfoBase->SetName((FText::FromName(mMonsterInfo.Name)));
	}
}
