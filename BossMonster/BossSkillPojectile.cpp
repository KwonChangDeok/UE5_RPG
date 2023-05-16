// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSkillPojectile.h"
#include "../Player/Skill/Decal.h"
#include "../Player/PlayerCharacter.h"
#include "RockGiant.h"
#include "SkillSoundActor.h"

// Sets default values
ABossSkillPojectile::ABossSkillPojectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // 충돌 컴포넌트 생성
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(_T("CollisionComponent"));
    CollisionComponent->InitSphereRadius(1.f);
    CollisionComponent->SetCollisionProfileName(_T("MonsterAttackObject"));
    CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel5);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->OnComponentHit.AddDynamic(this, &ABossSkillPojectile::OnProjectileHit);
    SetRootComponent(CollisionComponent);

    // 이동 컴포넌트 생성
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(_T("ProjectileMovementComponent"));
    ProjectileMovementComponent->InitialSpeed = 2000.f;
    ProjectileMovementComponent->MaxSpeed = 2000.f;
    ProjectileMovementComponent->ProjectileGravityScale = 1.0f;
    ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
    // 메쉬컴포넌트 생성
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(_T("ProjectileMesh"));
    StaticMeshComponent->SetupAttachment(CollisionComponent);
    StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    StaticMeshComponent->SetWorldScale3D(FVector(4.f, 4.f, 4.f));
}

// Called when the game starts or when spawned
void ABossSkillPojectile::BeginPlay()
{
	Super::BeginPlay();

    // 초를 구하기 위해 m단위로 통일
    float ZVelocity = ProjectileMovementComponent->Velocity.Z / 100.f;
    float ZLocation = GetActorLocation().Z / 100.f;
    float ZGravity = GetWorld()->GetGravityZ() / 100.f;

    float HitTime = (-ZVelocity - FMath::Sqrt(FMath::Pow(ZVelocity, 2) - 2.f * ZGravity * ZLocation)) / ZGravity;

    // 시간은 초, 단위는 cm
    HitLoc = GetActorLocation() + GetActorForwardVector() * HitTime * 2000.f;
    HitLoc.Z = 0.f;

    FActorSpawnParameters SpawnParam;
    SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    Decal = GetWorld()->SpawnActor<ADecal>(SpawnParam);
    Decal->SetDecalWorldLocation(HitLoc);

    FActorSpawnParameters SoundParam;
    SoundParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    ASkillSoundActor* Sound = GetWorld()->SpawnActor<ASkillSoundActor>(SoundParam);
    Sound->SetDelay(HitTime);
    Sound->SetLocation(HitLoc);
    Sound->SetLifeSpan(HitTime + 5.f);
}

// Called every frame
void ABossSkillPojectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    int32 RandDir = FMath::RandRange(0, 2);

    float RotValue = DeltaTime * 200.f;

    switch (RandDir)
    {
    case 0:
        AddActorLocalRotation(FRotator(RotValue, 0.f, 0.f));
        break;
    case 1:
        AddActorLocalRotation(FRotator(0.f, RotValue, 0.f));
        break;
    case 2:
        AddActorLocalRotation(FRotator(0.f, 0.f, RotValue));
        break;
    }
}

void ABossSkillPojectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    ARockGiant* Boss = Cast<ARockGiant>(UGameplayStatics::GetActorOfClass(GetWorld(), ARockGiant::StaticClass()));
    
    if(IsValid(Boss))
    {
        FCollisionQueryParams param(NAME_None, false, this);
        TArray<FHitResult> Result;

        bool Collision = GetWorld()->SweepMultiByChannel(Result, HitLoc, HitLoc, FQuat::Identity,
            ECollisionChannel::ECC_GameTraceChannel7, FCollisionShape::MakeSphere(500.f), param);

        if (Collision)
        {
            int32 Count = Result.Num();

            for (int32 i = 0; i < Count; i++)
            {
                float Damage = 500.f;

                APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Result[i].GetActor());
                if (IsValid(PlayerCharacter))
                {
                    Boss->SkillDamage(Damage, PlayerCharacter);
                }
            }
        }
    }

    Decal->Destroy();
    Destroy();
}