// Actor Ŭ������ ��ӹ޾� ��ġ�� 0.5�� �� �����ϴ� ��ų ���� ����� ����ϴ� Ŭ�����Դϴ�.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "SkillSoundActor.generated.h"

UCLASS()
class ASSASSIN_API ASkillSoundActor : public AActor
{
	GENERATED_BODY()
	
public:
	ASkillSoundActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
	USceneComponent* mRoot;

	FTimerHandle SoundTimer;

	FVector Location;

protected:
	virtual void BeginPlay() override;

public:
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
