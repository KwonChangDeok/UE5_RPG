/*
PlayerController 클래스를 상속받아 마우스 커서의 보이기 설정과 마우스 커서가 화면의 좌, 우 끝단에 위치할 시 
누적값을 PlayerCharacter의 카메라 회전 함수에 전달하는 역할을 합니다.
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
