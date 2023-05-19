/*
Actor 클래스를 상속받아 원형 고리형태로 캐릭터의 스킬 시전가능 범위를 표현해주기 위한 클래스입니다.
*/

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "DecalBoundary.generated.h"

UCLASS()
class ASSASSIN_API ADecalBoundary : public AActor
{
	GENERATED_BODY()
	
public:	
	ADecalBoundary();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UDecalComponent* mDecal;

	FVector mLocation;

	bool mTickKey;

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetDecalWorldLocation(FVector Location)
	{
		mLocation = Location;
		mTickKey = true;
	}
};
