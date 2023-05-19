/*
Actor Ŭ������ ��ӹ޾� ���� �����·� ĳ������ ��ų �������� ������ ǥ�����ֱ� ���� Ŭ�����Դϴ�.
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
