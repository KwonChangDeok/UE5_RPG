// Actor 클래스를 상속받아 리치 스킬의 충돌판정을 구현한 클래스입니다. 생성 후 0.5초 뒤 범위 내 플레이어가 있다면 데미지를 가합니다.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "LichSkill3Object.generated.h"

UCLASS()
class ASSASSIN_API ALichSkill3Object : public AActor
{
	GENERATED_BODY()
	
public:	
	ALichSkill3Object();

private:
	FTimerHandle BoomTimer;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
	USceneComponent* mRoot;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void Boom();

};
