// Actor 클래스를 상속받아 플레이어와 오버랩 이벤트 발생 시 이벤트 처리 함수를 바인딩 하는 기능을 수행합니다

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "BoxTriggerBase.generated.h"

UCLASS()
class ASSASSIN_API ABoxTriggerBase : public AActor
{
	GENERATED_BODY()
	
public:
	ABoxTriggerBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	USceneComponent* mRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UBoxComponent* mBox;

public:
	virtual void OnConstruction(const FTransform& Transform);

public:
	// 델리게이트에 등록할 함수
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	// 이벤트 발생시 간략화한 아래의 함수들을 호출하고, 이를 자식클래스에서 재정의하여 기능 구현
public:
	virtual void TriggerBegin(const FHitResult& SweepResult);
	virtual void TriggerEnd();
};
