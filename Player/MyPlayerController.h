/*
PlayerController Ŭ������ ��ӹ޾� ���콺 Ŀ���� ���̱� ������ ���콺 Ŀ���� ȭ���� ��, �� ���ܿ� ��ġ�� �� 
�������� PlayerCharacter�� ī�޶� ȸ�� �Լ��� �����ϴ� ������ �մϴ�.
*/
#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

UCLASS()
class ASSASSIN_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerController();

private:
	float RotationAccumulator;
	class APlayerCharacter* PlayerCharacter;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
