// Actor 클래스를 상속받아 캐릭터의 스킬 범위를 표현해주기 위한 데칼을 구현한 클래스입니다.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Decal.generated.h"

UCLASS()
class ASSASSIN_API ADecal : public AActor
{
	GENERATED_BODY()
	
public:	
	ADecal();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UDecalComponent* mDecal;

	FVector mLocation;

	bool mTickKey;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SetDecalWorldLocation(FVector Location)
	{
		mLocation = Location;
		mTickKey = true;
	}

};
