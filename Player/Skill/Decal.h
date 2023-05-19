// Actor Ŭ������ ��ӹ޾� ĳ������ ��ų ������ ǥ�����ֱ� ���� ��Į�� ������ Ŭ�����Դϴ�.

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
