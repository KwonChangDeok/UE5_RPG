#include "MyPlayerController.h"
#include "PlayerCharacter.h"

AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;

    RotationAccumulator = 0.f;
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetActorTickEnabled(true);

    PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
}

// 만약 커서가 인벤토리 위젯 위에 존재한다면, 마우스 이벤트를 인벤토리 위젯에서 처리하게 되므로 화면이 회전하지 않습니다.
void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    double MouseX, MouseY;
    GetMousePosition(MouseX, MouseY);

    int32 ViewportWidth, ViewportHeight;
    GetViewportSize(ViewportWidth, ViewportHeight);

    float RotationStep = 180.0f * DeltaTime;

    if (MouseX < 5.f)
    {
        RotationAccumulator -= RotationStep;
    }
    else if (MouseX >= ViewportWidth - 5.f)
    {
        RotationAccumulator += RotationStep;
    }

    if (IsValid(PlayerCharacter))
    {
        PlayerCharacter->AddActorWorldRotation(FRotator(0.f, RotationAccumulator, 0.f));
        PlayerCharacter->SetSpringArmRotation(RotationAccumulator);

        RotationAccumulator = 0.f;
    }
}