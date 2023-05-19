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

// ���� Ŀ���� �κ��丮 ���� ���� �����Ѵٸ�, ���콺 �̺�Ʈ�� �κ��丮 �������� ó���ϰ� �ǹǷ� ȭ���� ȸ������ �ʽ��ϴ�.
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