// Actor Ŭ������ ��ӹ޾� ��ġ ��ų�� �浹������ ������ Ŭ�����Դϴ�. ���� �� 0.5�� �� ���� �� �÷��̾ �ִٸ� �������� ���մϴ�.

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
