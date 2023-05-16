
#include "PlayerSkillProjectile.h"
#include "PlayerCharacter.h"
#include "../Monster/MonsterBase.h"
#include "../AssassinGameModeBase.h"

// Sets default values
APlayerSkillProjectile::APlayerSkillProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    // 충돌 컴포넌트 생성
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(_T("CollisionComponent"));
    CollisionComponent->InitSphereRadius(150.f);
    CollisionComponent->SetCollisionProfileName(_T("PlayerAttack"));
    CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->OnComponentHit.AddDynamic(this, &APlayerSkillProjectile::OnProjectileHit);
    SetRootComponent(CollisionComponent);

    // 이동 컴포넌트 생성
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(_T("ProjectileMovementComponent"));
    ProjectileMovementComponent->InitialSpeed = 4000.f;
    ProjectileMovementComponent->MaxSpeed = 4000.f;
    ProjectileMovementComponent->bRotationFollowsVelocity = false;
    ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);

    // 메쉬컴포넌트 생성
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(_T("ProjectileMesh"));
    StaticMeshComponent->SetupAttachment(CollisionComponent);
    StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    StaticMeshComponent->SetWorldScale3D(FVector(2.f, 2.f, 2.f));

    SkillDamage = 1.f;
    SkillRange = 4000.f;
    AccDistance = 0.f;
}

// Called when the game starts or when spawned
void APlayerSkillProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerSkillProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    AccDistance += 4000.f * DeltaTime;

    if (AccDistance >= SkillRange)
    {
        Destroy();
    }
}

void APlayerSkillProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    AMonsterBase* Monster = Cast<AMonsterBase>(OtherActor);

    if (IsValid(Monster) && IsValid(PlayerCharacter))
    {
        float Damage = SkillDamage * PlayerCharacter->GetPlayerInfo().AttackPoint * FMath::FRandRange(0.8, 1.2);
        Monster->SetCritical(false);

        // 크리티컬 데미지
        if (FMath::RandRange(1, 100) <= PlayerCharacter->GetPlayerInfo().CriticalRate)
        {
            Damage *= PlayerCharacter->GetPlayerInfo().CriticalDamage;
            Monster->SetCritical(true);
        }

        Monster->TakeDamage(Damage, FDamageEvent(), PlayerCharacter->GetController(), PlayerCharacter);
       
        PlayerCharacter->MakeParticle(GetActorLocation());
        
        PlayerCharacter->GetPlayerInfo().SpecialPoint = (PlayerCharacter->GetPlayerInfo().SpecialPoint + 10) > 100 ? 100 : (PlayerCharacter->GetPlayerInfo().SpecialPoint + 10);
        
        AAssassinGameModeBase* GameMode = Cast<AAssassinGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
        GameMode->GetMainUI()->SetSP(PlayerCharacter->GetPlayerInfo().SpecialPoint / 100.f);;
        GameMode->GetMainUI()->SetSkillZText(true);

        PlayerCharacter->SetSkillZSecondEnable(Monster);
    }

    Destroy();
}
