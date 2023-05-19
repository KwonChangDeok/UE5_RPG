// Actor 클래스를 상속받아 리치의 0.5초 뒤 폭발하는 스킬 사운드 재생을 담당하는 클래스입니다.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "SkillSoundActor.generated.h"

UCLASS()
class ASSASSIN_API ASkillSoundActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillSoundActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
	USceneComponent* mRoot;

	FTimerHandle SoundTimer;

	FVector Location;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PlaySound();

	void SetLocation(FVector Loc)
	{
		Location = Loc;
	}

	void SetDelay(float Seconds)
	{
		GetWorld()->GetTimerManager().SetTimer(SoundTimer, this, &ASkillSoundActor::PlaySound, Seconds, false, -1.f);
	}
};
