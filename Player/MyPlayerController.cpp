// Fill out your copyright notice in the Description page of Project Settings.


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