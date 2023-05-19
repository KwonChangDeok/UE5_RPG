// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PlayerAnimInstance.h"
#include "../AssassinGameInstance.h"
#include "../Monster/MonsterBase.h"
#include "./Skill/Shadow.h"
#include "./Skill/Decal.h"
#include "MyPlayerController.h"
#include "./Skill/DecalBoundary.h"
#include "../AssassinGameModeBase.h"
#include "../UMG/InventoryBase.h"
#include "../UMG/ItemObject.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(_T("SpringArm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(_T("Camera"));

	// 카메라 회전이 폰의 제어를 받지 않도록 설정
	mSpringArm->bUsePawnControlRotation = 0;
	mSpringArm->bInheritPitch = 0;
	mSpringArm->bInheritRoll = 0;
	mSpringArm->bInheritYaw = 0;

	mSpringArm->SetupAttachment(GetMesh());
	mCamera->SetupAttachment(mSpringArm);

	// 카메라 위치 조정
	mSpringArm->TargetArmLength = 500.f;
	mSpringArm->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	mSpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));

	mForwardScale = 0.f;
	mDeath = false;

	mSkillZTargetMonster = nullptr;
	mShadow = nullptr;
	mSkillXComeBackLocation = FVector::ZeroVector;

	UltimateLocation = FVector::ZeroVector;

	OrgLength = 0.f;
	DestLength = 500.f;

	TargetArmKey = false;

	// 현재 대쉬여부
	mDash = false;
	
	mPressedV = false;

	// 현재 스킬 사용가능여부
	mDashEnable = true;
	mSkillZFirstEnable = true;
	mSkillZSecondEnable = false;
	mSkillXFirstEnable = true;
	mSkillXSecondEnable = false;
	mSkillCEnable = true;
	mSkillVEnable = true;

	// 컨트롤러 제어 회전사용 OFF
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// 콜리전 채널 설정
	GetCapsuleComponent()->SetCollisionProfileName(_T("Player"));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SkillZAcc = 0.f;
	SkillXAcc = 0.f;
	SkillCAcc = 0.f;
	SkillVAcc = 0.f;
	DashAcc = 0.f;

	ConstructorHelpers::FClassFinder<UUserWidget> InventoryFinder(_T("WidgetBlueprint'/Game/Blueprint/UMG/UMG_Inventory.UMG_Inventory_C'"));
	if (InventoryFinder.Succeeded())
	{
		mInventoryBaseClass = InventoryFinder.Class;
		mWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(_T("Widget"));
		mWidgetComponent->SetWidgetClass(mInventoryBaseClass);
	}

	mItemIndex = 0;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UAssassinGameInstance* GameInstance = GetWorld()->GetGameInstance<UAssassinGameInstance>();
	
	const FPlayerTableInfo* Info = GameInstance->GetPlayerTable(mPlayerInfoRowName);

	// 유효성 검사 후 데이터테이블 초기화
	if (Info)
	{
		mPlayerInfo.AttackPoint = Info->AttackPoint;
		mPlayerInfo.ArmorPoint = Info->ArmorPoint;
		mPlayerInfo.HP = Info->HP;
		mPlayerInfo.HPMax = Info->HPMax;
		mPlayerInfo.MP = Info->MP;
		mPlayerInfo.MPMax = Info->MPMax;
		mPlayerInfo.Level = Info->Level;
		mPlayerInfo.LevelMax = Info->LevelMax;
		mPlayerInfo.Exp = Info->Exp;
		mPlayerInfo.SkillPoint = Info->SkillPoint;
		mPlayerInfo.MaxWalkSpeed = Info->MaxWalkSpeed;
		mPlayerInfo.CooldownReduction = Info->CooldownReduction;
		mPlayerInfo.CriticalRate = Info->CriticalRate;
		mPlayerInfo.CriticalDamage = Info->CriticalDamage;
		mPlayerInfo.AttackRange = Info->AttackRange;
		mPlayerInfo.SpecialPoint = Info->SpecialPoint;
		mPlayerInfo.Gold = 0;

		GetCharacterMovement()->MaxWalkSpeed = mPlayerInfo.MaxWalkSpeed;
	}
	
	mAnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	// 주기적으로 SP감소 및 MP를 회복
	GetWorldTimerManager().SetTimer(PlayerInfoTimer, this, &APlayerCharacter::SetPlayerInfoFromTime, 5.f, true, -1.f);
	
	AAssassinGameModeBase* GameMode = Cast<AAssassinGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	mMainUI = GameMode->GetMainUI();

	mMainUI->SetHP(mPlayerInfo.HP, mPlayerInfo.HPMax);
	mMainUI->SetMP(mPlayerInfo.MP, mPlayerInfo.MPMax);
	mMainUI->SetSP(mPlayerInfo.SpecialPoint / 100.f);

	mMainUI->SetSkillZBar(0.f);
	mMainUI->SetSkillXBar(0.f);
	mMainUI->SetSkillCBar(0.f);
	mMainUI->SetSkillVBar(0.f);

	mMainUI->SetSkillZText(false);
	mMainUI->SetSkillXText(false);

	mMainUI->SetSkillVBack(FLinearColor(1.f, 1.f, 1.f, 0.5f));

	mMainUI->SetDashBar(0.f);
	
	mWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mWidgetComponent->GetUserWidgetObject()->AddToViewport();
	mWidgetComponent->GetUserWidgetObject()->SetPositionInViewport(FVector2D(100.0, 100.0));
	mWidgetComponent->GetUserWidgetObject()->SetDesiredSizeInViewport(FVector2D(400.0, 600.0));
	mWidgetComponent->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
	mWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	mWidgetComponent->SetVisibility(false);

	// 유저위젯의 생성시점이 늦으므로 타이머를 이용해 초기화했습니다.
	// 정보를 찾아 본 결과 가장 늦게 생성된다는 PostLogin에서도 문제가 생겨 타이머를 이용하게 되었습니다.
	// 더욱 안정적인 게임을 만들기 위해선 타이머를 주기적으로 호출해 객체 할당을 시도하고, 할당 후 타이머핸들을 파괴하는 방법이 더욱 적절하다고
	// 생각합니다.
	GetWorldTimerManager().SetTimer(InitTimer, this, &APlayerCharacter::InitializeInven, 0.1f, false, -1.f);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 순간이동 시 카메라의 자연스러운 이동을 위해 선형보간을 이용한 TargetArmLength 길이 조정
	if (TargetArmKey)
	{
		SetTargetArmLength(DeltaTime);
	}

	if (mPressedV)
	{
		AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController());

		FHitResult	result;
		bool Hit = PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel8, false, result);

		if (Hit && FVector::Distance(GetActorLocation(), result.ImpactPoint) <= 1500.f)
		{
			Decal->SetDecalWorldLocation(result.ImpactPoint);
		}
		else
		{
			FVector Loc = result.ImpactPoint - (GetActorLocation() - FVector(0.f, 0.f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
			Loc.Z = 0.f;
			Loc.Normalize();
			Decal->SetDecalWorldLocation(GetActorLocation() + Loc * 1500.f);
		}

		if (GetActorLocation() != DecalBoundary->GetActorLocation())
		{
			DecalBoundary->SetDecalWorldLocation(GetActorLocation());
		}
	}
	else if(IsValid(Decal))
	{
		Decal->Destroy();
	}
	else if (IsValid(DecalBoundary))
	{
		DecalBoundary->Destroy();
	}

	if (!mSkillZFirstEnable)
	{
		float ZRatio = (SkillZCoolTime - SkillZAcc) / SkillZCoolTime;
		SkillZAcc += DeltaTime;

		if (ZRatio < 0.05f)
		{
			mMainUI->SetSkillZBar(0.f);
			mMainUI->SetSkillZText(false);
		}
		else
		{
			mMainUI->SetSkillZBar(ZRatio);
		}
	}
	
	if (!mSkillXFirstEnable)
	{
		float XRatio = (SkillXCoolTime - SkillXAcc) / SkillXCoolTime;
		SkillXAcc += DeltaTime;

		if (XRatio < 0.05f)
		{
			mMainUI->SetSkillXBar(0.f);
			mMainUI->SetSkillXText(false);
		}
		else
		{
			mMainUI->SetSkillXBar(XRatio);
		}
	}

	if (!mSkillCEnable)
	{
		float CRatio = (SkillCCoolTime - SkillCAcc) / SkillCCoolTime;
		SkillCAcc += DeltaTime;

		if (CRatio < 0.05f)
		{
			mMainUI->SetSkillCBar(0.f);
		}
		else
		{
			mMainUI->SetSkillCBar(CRatio);
		}
	}

	if (!mSkillVEnable)
	{
		float VRatio = (SkillVCoolTime - SkillVAcc) / SkillVCoolTime;
		SkillVAcc += DeltaTime;

		if (VRatio < 0.05f)
		{
			mMainUI->SetSkillVBar(0.f);
		}
		else
		{
			mMainUI->SetSkillVBar(VRatio);
		}
	}
	else
	{
		if (mPlayerInfo.SpecialPoint == 100)
		{
			mMainUI->SetSkillVBack(FLinearColor(1.f, 0.f, 0.f, 1.f));
		}
		else
		{
			mMainUI->SetSkillVBack(FLinearColor(1.f, 1.f, 1.f, 0.5f));
		}
	}

	if (!mDashEnable)
	{
		float DashRatio = (DashCoolTime - DashAcc) / DashCoolTime;
		DashAcc += DeltaTime;

		if (DashRatio < 0.05f)
		{
			mMainUI->SetDashBar(0.f);
		}
		else
		{
			mMainUI->SetDashBar(DashRatio);
		}
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 축매핑 바인딩
	PlayerInputComponent->BindAxis<APlayerCharacter>(_T("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis<APlayerCharacter>(_T("MoveSide"), this, &APlayerCharacter::MoveSide);

	// 액션매핑 바인딩
	PlayerInputComponent->BindAction<APlayerCharacter>(_T("Jump"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SpaceBar);
	PlayerInputComponent->BindAction<APlayerCharacter>(_T("Attack"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Attack);
	PlayerInputComponent->BindAction<APlayerCharacter>(_T("Dash"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Dash);
	PlayerInputComponent->BindAction<APlayerCharacter>(_T("SkillZ"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SkillZ);
	PlayerInputComponent->BindAction<APlayerCharacter>(_T("SkillX"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SkillX);
	PlayerInputComponent->BindAction<APlayerCharacter>(_T("SkillC"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SkillC);
	PlayerInputComponent->BindAction<APlayerCharacter>(_T("SkillV"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SkillV);
	PlayerInputComponent->BindAction<APlayerCharacter>(_T("Turn"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAction<APlayerCharacter>(_T("Inventory"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Inventory);
	PlayerInputComponent->BindAction<APlayerCharacter>(_T("Attack"), EInputEvent::IE_Released, this, &APlayerCharacter::BtnUpEvent);
	PlayerInputComponent->BindAction<APlayerCharacter>(_T("QuickSlot1"), EInputEvent::IE_Released, this, &APlayerCharacter::QuickSlot1);
	PlayerInputComponent->BindAction<APlayerCharacter>(_T("QuickSlot2"), EInputEvent::IE_Released, this, &APlayerCharacter::QuickSlot2);
	PlayerInputComponent->BindAction<APlayerCharacter>(_T("QuickSlot3"), EInputEvent::IE_Released, this, &APlayerCharacter::QuickSlot3);
	PlayerInputComponent->BindAction<APlayerCharacter>(_T("QuickSlot4"), EInputEvent::IE_Released, this, &APlayerCharacter::QuickSlot4);
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// 삼항 연산자를 쓰는것이 선호되지 않을 수도 있다고 알고있습니다. 이런 부분은 적극적으로 팀원들에게 맞추겠습니다.
	float Damage = (DamageAmount - mPlayerInfo.ArmorPoint) > 1.f ? (DamageAmount - mPlayerInfo.ArmorPoint) : 1.f;

	mPlayerInfo.HP -= Damage;
	mMainUI->SetHP(mPlayerInfo.HP, mPlayerInfo.HPMax);

	if (mPlayerInfo.HP <= 0)
	{
		mDeath = true;
		mPlayerInfo.HP = 0;

		GetWorldTimerManager().SetTimer(ResurrectionTimer, this, &APlayerCharacter::Resurrection, 5.f, false, -1.f);
	}

	mAnimInst->Hit();
	
	// 최종적으로 사용하는 클래스이므로 아무값이나 반환.
	return 0.f;
}

void APlayerCharacter::MoveForward(float scale)
{
	mForwardScale = scale;

	if (mDeath || scale == 0.f || !mAnimInst->PlayerMoveEnable())
	{
		return;
	}

	// 카메라가 회전해 엑터가 카메라의 정면방향을 바라보고 있지 않더라도, 플레이어의 이동은 카메라의 정면을 기준으로 해야한다고 생각했습니다.
	if (FMath::Abs(GetActorRotation().Yaw - mSpringArm->GetRelativeRotation().Yaw) > 2.f)
	{
		SetActorRotation(FRotator(0.f, mSpringArm->GetRelativeRotation().Yaw, 0.f));
	}

	AddMovementInput(GetActorForwardVector(), scale);
}

void APlayerCharacter::MoveSide(float scale)
{
	if (mDeath || mDash || !mAnimInst->PlayerMoveEnable())
	{
		return;
	}

	float MoveDir = mAnimInst->GetMoveDir();

	if (scale != 0)
	{
		if (FMath::Abs(GetActorRotation().Yaw - mSpringArm->GetRelativeRotation().Yaw) > 2.f)
		{
			SetActorRotation(FRotator(0.f, mSpringArm->GetRelativeRotation().Yaw, 0.f));
		}
	}

	if (mForwardScale == 0.f)
	{
		if (scale == 0.f)
		{
			mAnimInst->SetMoveDir(0.f);
		}
		else if (scale == 1.f)
		{
			mAnimInst->SetMoveDir(90.f);
		}
		else
		{
			mAnimInst->SetMoveDir(-90.f);
		}
	}
	// 대각선 이동을 구현할때, 보다 자연스러운 애니메이션의 전환을 위해 점진적으로 애니메이션의 회전각을 변경하는 방법을 사용했습니다.
	// 하지만 사용한 애니메이션 에셋이 다소 자연스럽지 못한 부분이 있어 부분적으로만 적용하게 되었으며
	// 각도량에 변화를 줄 때, 델타타임을 곱해 언제나 일정한 결과를 얻을 수 있도록 구현해야 했지만, 이를 알고있음에도 실수를 했습니다.
	else if (mForwardScale == 1.f)
	{
		if (scale == 0.f)
		{
			mAnimInst->SetMoveDir(0.f);
		}
		else if (scale == 1.f)
		{
			if (MoveDir > 45.f)
			{
				MoveDir = (MoveDir - 200.f*GetWorld()->GetDeltaSeconds()) > 45.f ? (MoveDir - 200.f * GetWorld()->GetDeltaSeconds()) : 45.f;
			}
			else if (MoveDir < 45.f)
			{
				MoveDir = (MoveDir + 200.f * GetWorld()->GetDeltaSeconds()) < 45.f ? (MoveDir + 200.f * GetWorld()->GetDeltaSeconds()) : 45.f;
			}
			mAnimInst->SetMoveDir(MoveDir);
		}
		else
		{
			if (MoveDir > -45.f)
			{
				MoveDir = (MoveDir - 200.f * GetWorld()->GetDeltaSeconds()) > -45.f ? (MoveDir - 200.f * GetWorld()->GetDeltaSeconds()) : -45.f;
			}
			else if (MoveDir < -45.f)
			{
				MoveDir = (MoveDir + 200.f * GetWorld()->GetDeltaSeconds()) < -45.f ? (MoveDir + 200.f * GetWorld()->GetDeltaSeconds()) : -45.f;
			}
			mAnimInst->SetMoveDir(MoveDir);
		}
	}
	else
	{
		if (scale == 0.f)
		{
			mAnimInst->SetMoveDir(180.f);
		}
		else if (scale == 1.f)
		{
			if (MoveDir > 135.f)
			{
				MoveDir = (MoveDir - 200.f * GetWorld()->GetDeltaSeconds()) > 135.f ? (MoveDir - 200.f * GetWorld()->GetDeltaSeconds()) : 135.f;
			}
			else if (MoveDir < 135.f)
			{
				MoveDir = (MoveDir + 200.f * GetWorld()->GetDeltaSeconds()) < 135.f ? (MoveDir + 200.f * GetWorld()->GetDeltaSeconds()) : 135.f;
			}
			mAnimInst->SetMoveDir(MoveDir);
		}
		else
		{
			MoveDir = 135.f;
			mAnimInst->SetMoveDir(MoveDir);
		}
	}

	AddMovementInput(GetActorRightVector(), scale);
}

void APlayerCharacter::SpaceBar()
{
	if (mDeath)
	{
		return;
	}

	mPressedV = false;

	Jump();
}

void APlayerCharacter::Attack()
{
	if (mDeath)
	{
		return;
	}

	// 만약 v키가 활성화 된 후 v를 누른상태라면, 좌클릭을 통해 v스킬을 사용할 수 있도록 구현했습니다.
	// 그렇지 않다면 기본 콤보공격을 발동합니다.
	if (mPressedV == false)
	{
		mAnimInst->Attack();
	}
	else
	{
		mSkillVEnable = false;
		SkillVAcc = 0.f;
		mMainUI->SetSkillVBack(FLinearColor(1.f, 1.f, 1.f, 0.5f));

		mPlayerInfo.SpecialPoint = 0;
		mMainUI->SetSP(0.f);

		GetWorldTimerManager().SetTimer(SkillVTimer, this, &APlayerCharacter::SetSkillVEnable, 10.f, false, -1.f);

		UltimateLocation = Decal->GetActorLocation();

		mPressedV = false;

		GetMovementComponent()->StopMovementImmediately();
		GetCharacterMovement()->JumpZVelocity = 1000.f;
		Jump();

		mAnimInst->Ultimate();
	}
}

void APlayerCharacter::Dash()
{
	if (mDeath)
	{
		return;
	}

	if (mDashEnable)
	{
		mAnimInst->Skill(0);

		mDashEnable = false;
		DashAcc = 0.f;

		GetWorldTimerManager().SetTimer(DashTimer, this, &APlayerCharacter::SetDashEnable, 5.f, false, -1.f);

		mPressedV = false;
	}
}

void APlayerCharacter::SkillZ()
{
	if (mDeath)
	{
		return;
	}

	if (mSkillZFirstEnable && mAnimInst->GetSkillEnable() && (mPlayerInfo.MP > 50))
	{
		mPressedV = false;
		mSkillZTargetMonster = nullptr;
		mAnimInst->Skill(1);

		mPlayerInfo.MP -= 50;
		mMainUI->SetMP(mPlayerInfo.MP, mPlayerInfo.MPMax);

		mSkillZFirstEnable = false;
		SkillZAcc = 0.f;

		GetWorldTimerManager().SetTimer(SkillZTimer, this, &APlayerCharacter::SetSkillZFirstEnable, 10.f, false, -1.f);
	}
	else if (mSkillZSecondEnable && mAnimInst->GetSkillEnable())
	{
		mPressedV = false;
		mSkillZSecondEnable = false;
		mMainUI->SetSkillZText(false);
		
		if (IsValid(mSkillZTargetMonster))
		{
			FVector TargetLoc = mSkillZTargetMonster->GetActorLocation() +
				GetActorForwardVector() * mSkillZTargetMonster->GetCapsuleComponent()->GetScaledCapsuleRadius();

			SetActorLocation(TargetLoc);

			Turn();

			mAnimInst->Skill(2);
		}
	}
}

void APlayerCharacter::SkillX()
{
	if (mDeath)
	{
		return;
	}

	if (mSkillXFirstEnable && mAnimInst->GetSkillEnable() && (mPlayerInfo.MP > 50))
	{
		mPressedV = false;
		mSkillXComeBackLocation = FVector::ZeroVector;
		
		mAnimInst->Skill(3);

		mPlayerInfo.MP -= 50;
		mMainUI->SetMP(mPlayerInfo.MP, mPlayerInfo.MPMax);

		mSkillXFirstEnable = false;
		SkillXAcc = 0.f;
		mMainUI->SetSkillXText(true);

		mShadow = nullptr;
		GetWorldTimerManager().SetTimer(SkillXTimer, this, &APlayerCharacter::SetSkillXFirstEnable, 10.f, false, -1.f);
	}
	else if (mSkillXSecondEnable && mAnimInst->GetSkillEnable())
	{
		if (mSkillXComeBackLocation != FVector::ZeroVector)
		{
			mPressedV = false;
			mSkillXSecondEnable = false;
			mMainUI->SetSkillXText(false);

			if (IsValid(mShadow))
			{
				mShadow->Destroy();
				mShadow = nullptr;
			}

			FVector TargetLoc = mSkillXComeBackLocation;

			float Distance = FVector::Distance(TargetLoc, GetActorLocation());
			
			OrgLength = 600.f + Distance;
			mSpringArm->TargetArmLength = OrgLength;
			TargetArmKey = true;

			SetActorLocation(TargetLoc);

			mAnimInst->Skill(2);
		}
	}
}

void APlayerCharacter::SkillC()
{
	if (mDeath)
	{
		return;
	}

	if (mSkillCEnable && mAnimInst->GetSkillEnable() && (mPlayerInfo.MP > 100))
	{
		mPressedV = false;
		mSkillCEnable = false;
		SkillCAcc = 0.f;

		GetWorldTimerManager().SetTimer(SkillCTimer, this, &APlayerCharacter::SetSkillCEnable, 10.f, false, -1.f);
		mAnimInst->Skill(4);

		mPlayerInfo.MP -= 100;
		mMainUI->SetMP(mPlayerInfo.MP, mPlayerInfo.MPMax);
	}
}

void APlayerCharacter::SkillV()
{
	if (mDeath)
	{
		return;
	}

	UInventoryBase* mInventory = Cast<UInventoryBase>(mWidgetComponent->GetWidget());
	if (mInventory->GetCursorOnUI())
	{
		return;
	}

	if (mSkillVEnable && mAnimInst->GetSkillEnable() && !mPressedV && (mPlayerInfo.SpecialPoint == 100))
	{
		mPressedV = true;

		FActorSpawnParameters SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FActorSpawnParameters SpawnBoundaryParam;
		SpawnBoundaryParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		Decal = GetWorld()->SpawnActor<ADecal>(SpawnParam);
		DecalBoundary = GetWorld()->SpawnActor<ADecalBoundary>(SpawnBoundaryParam);
	}
}

void APlayerCharacter::Turn()
{
	if (mDeath)
	{
		return;
	}
	SetActorRotation(FRotator(0.f, GetActorRotation().Yaw + 180.f, 0.f));
	mSpringArm->SetRelativeRotation(FRotator(-15.f, GetActorRotation().Yaw, 0.f));
}

void APlayerCharacter::Inventory()
{
	if (mWidgetComponent->GetUserWidgetObject()->GetVisibility() == ESlateVisibility::Hidden)
	{
		mWidgetComponent->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		mWidgetComponent->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
	}
}

// 인벤토리 위젯 영역 외부에서 발생한 버튼 업 이벤트를 처리할 필요가 있었습니다.
// 드래그 중인 아이템이있다면, 실행을 취소하도록 하는 기능을 합니다.
void APlayerCharacter::BtnUpEvent()
{
	UInventoryBase* mInventory = Cast<UInventoryBase>(mWidgetComponent->GetWidget());

	if (IsValid(mInventory))
	{
		if (mInventory->GetVisibility() == ESlateVisibility::Visible)
		{
			mInventory->MouseButtonUp();
		}
	}

	if (IsValid(mMainUI))
	{
		mMainUI->MouseButtonUp();
	}
}


// 퀵슬롯 1, 2, 3, 4에 맵핑된 함수들은 같은 로직을 중복적으로 작성하여 가독성을 크게 해친다고 생각합니다.
// 중복되는 내용을 따로 함수화 해 중복을 제거하는 것이 바람직하다고 생각합니다.
void APlayerCharacter::QuickSlot1()
{
	int32 SlotNum = 1;

	if (IsValid(mMainUI))
	{
		// 슬롯에 있는 아이템정보를 인벤토리에서 찾는다.
		UItemObject* Item = mMainUI->GetSlotItem(SlotNum);

		if (IsValid(Item))
		{
			for (int32 i = 0; i < ItemArray.Num(); i++)
			{
				if (Item->GetItemID() == ItemArray[i].ID)
				{
					if (ItemArray[i].NumberOfItem == 0)
					{
						return;
					}

					ItemArray[i].NumberOfItem -= 1;

					// 인벤토리 아이템 정보 갱신
					UInventoryBase* mInventory = Cast<UInventoryBase>(mWidgetComponent->GetWidget());
					if (IsValid(mInventory))
					{
						mInventory->EditItem(ItemArray[i].ID, ItemArray[i].NumberOfItem);
					}

					// 퀵슬롯 아이템 정보 갱신
					mMainUI->ConsumeItem(SlotNum);

					// 아이템 사용 효과 적용
					mPlayerInfo.HP = mPlayerInfo.HP + ItemArray[i].HPHeal > mPlayerInfo.HPMax ?
						mPlayerInfo.HPMax : mPlayerInfo.HP + ItemArray[i].HPHeal;

					mPlayerInfo.MP = mPlayerInfo.MP + ItemArray[i].MPHeal > mPlayerInfo.MPMax ?
						mPlayerInfo.MPMax : mPlayerInfo.MP + ItemArray[i].MPHeal;

					mPlayerInfo.SpecialPoint = mPlayerInfo.SpecialPoint + ItemArray[i].SPHeal > 100 ?
						100 : mPlayerInfo.SpecialPoint + ItemArray[i].SPHeal;

					mMainUI->SetHP(mPlayerInfo.HP, mPlayerInfo.HPMax);
					mMainUI->SetMP(mPlayerInfo.MP, mPlayerInfo.MPMax);
					mMainUI->SetSP(mPlayerInfo.SpecialPoint / 100.f);
				}
			}
		}
	}
}

void APlayerCharacter::QuickSlot2()
{
	int32 SlotNum = 2;

	if (IsValid(mMainUI))
	{
		// 슬롯에 있는 아이템정보를 인벤토리에서 찾는다.
		UItemObject* Item = mMainUI->GetSlotItem(SlotNum);

		if (IsValid(Item))
		{
			for (int32 i = 0; i < ItemArray.Num(); i++)
			{
				if (Item->GetItemID() == ItemArray[i].ID)
				{
					if (ItemArray[i].NumberOfItem == 0)
					{
						return;
					}

					ItemArray[i].NumberOfItem -= 1;

					// 인벤토리 아이템 정보 갱신
					UInventoryBase* mInventory = Cast<UInventoryBase>(mWidgetComponent->GetWidget());
					if (IsValid(mInventory))
					{
						mInventory->EditItem(ItemArray[i].ID, ItemArray[i].NumberOfItem);
					}

					// 퀵슬롯 아이템 정보 갱신
					mMainUI->ConsumeItem(SlotNum);

					// 아이템 사용 효과 적용
					mPlayerInfo.HP = mPlayerInfo.HP + ItemArray[i].HPHeal > mPlayerInfo.HPMax ?
						mPlayerInfo.HPMax : mPlayerInfo.HP + ItemArray[i].HPHeal;

					mPlayerInfo.MP = mPlayerInfo.MP + ItemArray[i].MPHeal > mPlayerInfo.MPMax ?
						mPlayerInfo.MPMax : mPlayerInfo.MP + ItemArray[i].MPHeal;

					mPlayerInfo.SpecialPoint = mPlayerInfo.SpecialPoint + ItemArray[i].SPHeal > 100 ?
						100 : mPlayerInfo.SpecialPoint + ItemArray[i].SPHeal;

					mMainUI->SetHP(mPlayerInfo.HP, mPlayerInfo.HPMax);
					mMainUI->SetMP(mPlayerInfo.MP, mPlayerInfo.MPMax);
					mMainUI->SetSP(mPlayerInfo.SpecialPoint / 100.f);
				}
			}
		}
	}
}

void APlayerCharacter::QuickSlot3()
{
	int32 SlotNum = 3;

	if (IsValid(mMainUI))
	{
		// 슬롯에 있는 아이템정보를 인벤토리에서 찾는다.
		UItemObject* Item = mMainUI->GetSlotItem(SlotNum);

		if (IsValid(Item))
		{
			for (int32 i = 0; i < ItemArray.Num(); i++)
			{
				if (Item->GetItemID() == ItemArray[i].ID)
				{
					if (ItemArray[i].NumberOfItem == 0)
					{
						return;
					}

					ItemArray[i].NumberOfItem -= 1;

					// 인벤토리 아이템 정보 갱신
					UInventoryBase* mInventory = Cast<UInventoryBase>(mWidgetComponent->GetWidget());
					if (IsValid(mInventory))
					{
						mInventory->EditItem(ItemArray[i].ID, ItemArray[i].NumberOfItem);
					}

					// 퀵슬롯 아이템 정보 갱신
					mMainUI->ConsumeItem(SlotNum);

					// 아이템 사용 효과 적용
					mPlayerInfo.HP = mPlayerInfo.HP + ItemArray[i].HPHeal > mPlayerInfo.HPMax ?
						mPlayerInfo.HPMax : mPlayerInfo.HP + ItemArray[i].HPHeal;

					mPlayerInfo.MP = mPlayerInfo.MP + ItemArray[i].MPHeal > mPlayerInfo.MPMax ?
						mPlayerInfo.MPMax : mPlayerInfo.MP + ItemArray[i].MPHeal;

					mPlayerInfo.SpecialPoint = mPlayerInfo.SpecialPoint + ItemArray[i].SPHeal > 100 ?
						100 : mPlayerInfo.SpecialPoint + ItemArray[i].SPHeal;

					mMainUI->SetHP(mPlayerInfo.HP, mPlayerInfo.HPMax);
					mMainUI->SetMP(mPlayerInfo.MP, mPlayerInfo.MPMax);
					mMainUI->SetSP(mPlayerInfo.SpecialPoint / 100.f);
				}
			}
		}
	}
}

void APlayerCharacter::QuickSlot4()
{
	int32 SlotNum = 4;

	if (IsValid(mMainUI))
	{
		// 슬롯에 있는 아이템정보를 인벤토리에서 찾는다.
		UItemObject* Item = mMainUI->GetSlotItem(SlotNum);

		if (IsValid(Item))
		{
			for (int32 i = 0; i < ItemArray.Num(); i++)
			{
				if (Item->GetItemID() == ItemArray[i].ID)
				{
					if (ItemArray[i].NumberOfItem == 0)
					{
						return;
					}

					ItemArray[i].NumberOfItem -= 1;

					// 인벤토리 아이템 정보 갱신
					UInventoryBase* mInventory = Cast<UInventoryBase>(mWidgetComponent->GetWidget());
					if (IsValid(mInventory))
					{
						mInventory->EditItem(ItemArray[i].ID, ItemArray[i].NumberOfItem);
					}

					// 퀵슬롯 아이템 정보 갱신
					mMainUI->ConsumeItem(SlotNum);

					// 아이템 사용 효과 적용
					mPlayerInfo.HP = mPlayerInfo.HP + ItemArray[i].HPHeal > mPlayerInfo.HPMax ?
						mPlayerInfo.HPMax : mPlayerInfo.HP + ItemArray[i].HPHeal;

					mPlayerInfo.MP = mPlayerInfo.MP + ItemArray[i].MPHeal > mPlayerInfo.MPMax ?
						mPlayerInfo.MPMax : mPlayerInfo.MP + ItemArray[i].MPHeal;

					mPlayerInfo.SpecialPoint = mPlayerInfo.SpecialPoint + ItemArray[i].SPHeal > 100 ?
						100 : mPlayerInfo.SpecialPoint + ItemArray[i].SPHeal;

					mMainUI->SetHP(mPlayerInfo.HP, mPlayerInfo.HPMax);
					mMainUI->SetMP(mPlayerInfo.MP, mPlayerInfo.MPMax);
					mMainUI->SetSP(mPlayerInfo.SpecialPoint / 100.f);
				}
			}
		}
	}
}

void APlayerCharacter::SetSkillXFirstEnable()
{
	mSkillXFirstEnable = true;
	mSkillXSecondEnable = false;
	if (IsValid(mShadow))
	{
		mShadow->Destroy();
		mShadow = nullptr;
	}
}

void APlayerCharacter::InitializeInven()
{
	for(int32 i = 0; i < 60; i++)
	{
		AddItem(FName(_T("Blank")));
	}

	AddItem(FName(_T("HP_POTION")));
	AddItem(FName(_T("MP_POTION")));
	AddItem(FName(_T("HP_POTION")));

	UInventoryBase* mInventory = Cast<UInventoryBase>(mWidgetComponent->GetWidget());
	mInventory->SetGold(mPlayerInfo.Gold);
}

void APlayerCharacter::AddItem(FName ItemID)
{
	UInventoryBase* mInventory = Cast<UInventoryBase>(mWidgetComponent->GetWidget());

	if (IsValid(mInventory))
	{
		UAssassinGameInstance* GameInstance = GetWorld()->GetGameInstance<UAssassinGameInstance>();

		const FItemDataInfo* Info = GameInstance->GetItemTable(ItemID);

		if (Info)
		{
			for (int32 i = 0; i < ItemArray.Num(); i++)
			{
				if (ItemArray[i].ID == ConvertFromFNameToItemEnum(ItemID) && Info->ItemType == EITEM_TYPE::CONSUMABLE)
				{
					ItemArray[i].NumberOfItem++;
					mInventory->EditItem(ItemArray[i].ID, ItemArray[i].NumberOfItem);
					return;
				}
			}

			FItemDataInfo mItemInfo;
			mItemInfo.ID = Info->ID;
			mItemInfo.ItemType = Info->ItemType;
			mItemInfo.ItemName = Info->ItemName;
			mItemInfo.Description = Info->Description;
			mItemInfo.IconPath = Info->IconPath;
			mItemInfo.LimitLevel = Info->LimitLevel;
			mItemInfo.NumberOfItem = Info->NumberOfItem;
			mItemInfo.ItemIndex = mItemIndex;
			mItemIndex++;
			mItemInfo.HPHeal = Info->HPHeal;
			mItemInfo.MPHeal = Info->MPHeal;
			mItemInfo.SPHeal = Info->SPHeal;
			mItemInfo.AttackPoint = Info->AttackPoint;
			mItemInfo.ArmorPoint = Info->ArmorPoint;
			mItemInfo.CooldownReduction = Info->CooldownReduction;
			mItemInfo.CriticalRate = Info->CriticalRate;
			mItemInfo.CriticalDamage = Info->CriticalDamage;

			if (mItemInfo.ItemType != EITEM_TYPE::Blank)
			{
				ItemArray.Add(mItemInfo);
			}

			mInventory->AddItem(mItemInfo);
		}
	}
}

void APlayerCharacter::AddGold(int32 Value)
{
	mPlayerInfo.Gold += Value;

	UInventoryBase* mInventory = Cast<UInventoryBase>(mWidgetComponent->GetWidget());

	if (IsValid(mInventory))
	{
		mInventory->SetGold(mPlayerInfo.Gold);
	}
}

void APlayerCharacter::SetTargetArmLength(float DeltaTime)
{
	float InterpSpeed = 5.f;

	float NewLength = FMath::FInterpTo(OrgLength, DestLength, DeltaTime, InterpSpeed);
	
	OrgLength = NewLength;

	mSpringArm->TargetArmLength = NewLength;
}

void APlayerCharacter::FootStep(bool Left)
{
	FVector	LineStart;

	if (Left)
	{
		LineStart = GetMesh()->GetSocketLocation(_T("Foot_L"));
	}
	else
	{
		LineStart = GetMesh()->GetSocketLocation(_T("Foot_R"));
	}

	FVector	LineEnd = LineStart + FVector::DownVector * 50.f;

	FCollisionQueryParams param(NAME_None, false, this);

	param.bReturnPhysicalMaterial = true;

	FHitResult	result;
	bool Hit = GetWorld()->LineTraceSingleByChannel(result, LineStart, LineEnd, ECollisionChannel::ECC_GameTraceChannel10, param);

	if (Hit)
	{
		UPhysicalMaterial* MyPhysMaterial = result.PhysMaterial.Get();
		if (MyPhysMaterial != nullptr)
		{
			FString Plastic = "PhysicalMaterial'/Game/FootstepSound/Materials/Physical_Materials/07_Plastic_Physic_Mat.07_Plastic_Physic_Mat'";
			UPhysicalMaterial* PlasticMaterial = Cast<UPhysicalMaterial>(StaticLoadObject(UPhysicalMaterial::StaticClass(), NULL, *Plastic));

			FString Concrete = "PhysicalMaterial'/Game/FootstepSound/Materials/Physical_Materials/02_Conrete_Physic_Mat.02_Conrete_Physic_Mat'";
			UPhysicalMaterial* ConcreteMaterial = Cast<UPhysicalMaterial>(StaticLoadObject(UPhysicalMaterial::StaticClass(), NULL, *Concrete));

			FString Metal = "PhysicalMaterial'/Game/FootstepSound/Materials/Physical_Materials/06_Metal_Physic_Mat.06_Metal_Physic_Mat'";
			UPhysicalMaterial* MetalMaterial = Cast<UPhysicalMaterial>(StaticLoadObject(UPhysicalMaterial::StaticClass(), NULL, *Metal));

			FString Ground = "PhysicalMaterial'/Game/FootstepSound/Materials/Physical_Materials/05_Ground_Physic_Mat.05_Ground_Physic_Mat'";
			UPhysicalMaterial* GroundMaterial = Cast<UPhysicalMaterial>(StaticLoadObject(UPhysicalMaterial::StaticClass(), NULL, *Ground));

			if (MyPhysMaterial == PlasticMaterial)
			{
				USoundWave* Sound = LoadObject<USoundWave>(nullptr, _T("SoundWave'/Game/FootstepSound/Sounds/WaveFiles/Footsteps_Mono/Female/Plastic/PlasticHeels_6.PlasticHeels_6'"));

				if (IsValid(Sound))
				{
					UGameplayStatics::PlaySound2D(this, Sound);
				}
			}
			else if (MyPhysMaterial == MetalMaterial)
			{
				USoundWave* Sound = LoadObject<USoundWave>(nullptr, _T("SoundWave'/Game/FootstepSound/Sounds/WaveFiles/Footsteps_Mono/Female/Metal/Metal_Heels_4.Metal_Heels_4'"));

				if (IsValid(Sound))
				{
					UGameplayStatics::PlaySound2D(this, Sound);
				}
			}
			else if (MyPhysMaterial == GroundMaterial)
			{
				USoundWave* Sound = LoadObject<USoundWave>(nullptr, _T("SoundWave'/Game/FootstepSound/Sounds/WaveFiles/Footsteps_Mono/Female/Ground/Ground_Heels_1.Ground_Heels_1'"));

				if (IsValid(Sound))
				{
					UGameplayStatics::PlaySound2D(this, Sound);
				}
			}
			else
			{
				USoundWave* Sound = LoadObject<USoundWave>(nullptr, _T("SoundWave'/Game/FootstepSound/Sounds/WaveFiles/Footsteps_Mono/Female/Concrete/Concrete_Heels_2.Concrete_Heels_2'"));

				if (IsValid(Sound))
				{
					UGameplayStatics::PlaySound2D(this, Sound);
				}
			}
		}
		else
		{
			USoundWave* Sound = LoadObject<USoundWave>(nullptr, _T("SoundWave'/Game/FootstepSound/Sounds/WaveFiles/Footsteps_Mono/Female/Concrete/Concrete_Heels_2.Concrete_Heels_2'"));

			if (IsValid(Sound))
			{
				UGameplayStatics::PlaySound2D(this, Sound);
			}
		}
	}
}

void APlayerCharacter::SetDragItem(UItemObject* DragItem)
{
	mDragItem = NewObject<UItemObject>();

	if (IsValid(DragItem))
	{
		mDragItem->SetIconPath(DragItem->GetIconPath());
		mDragItem->SetItemCount(DragItem->GetItemCount());
		mDragItem->SetItemName(DragItem->GetItemName());
		mDragItem->SetItemDescription(DragItem->GetItemDescription());
		mDragItem->SetItemID(DragItem->GetItemID());
		mDragItem->SetIsBlank(DragItem->GetIsBlank());
	}
	else
	{
		mDragItem = nullptr;
	}
}

void APlayerCharacter::TossItem()
{
	UInventoryBase* mInventory = Cast<UInventoryBase>(mWidgetComponent->GetWidget());
	
	if (IsValid(mInventory))
	{
		mInventory->TossItem();
	}
}
