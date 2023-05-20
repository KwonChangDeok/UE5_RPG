// Actor Ŭ������ ��ӹ޾� �÷��̾�� ������ �̺�Ʈ �߻� �� �̺�Ʈ ó�� �Լ��� ���ε� �ϴ� ����� �����մϴ�

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
	// ��������Ʈ�� ����� �Լ�
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	// �̺�Ʈ �߻��� ����ȭ�� �Ʒ��� �Լ����� ȣ���ϰ�, �̸� �ڽ�Ŭ�������� �������Ͽ� ��� ����
public:
	virtual void TriggerBegin(const FHitResult& SweepResult);
	virtual void TriggerEnd();
};
