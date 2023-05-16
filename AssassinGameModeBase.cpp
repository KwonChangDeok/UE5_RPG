// Copyright Epic Games, Inc. All Rights Reserved.


#include "AssassinGameModeBase.h"
#include "Player/MyPlayerController.h"
#include "Player/AssassinCharacter.h"
#include "UMG/MainUIBase.h"

AAssassinGameModeBase::AAssassinGameModeBase()
{
	DefaultPawnClass = AAssassinCharacter::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();

	ConstructorHelpers::FClassFinder<UUserWidget> finder(_T("WidgetBlueprint'/Game/Blueprint/UMG/UMG_MainUI.UMG_MainUI_C'"));
	if (finder.Succeeded())
	{
		mMainUIClass = finder.Class;
	}
}

void AAssassinGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(mMainUIClass))
	{
		mMainUI = Cast<UMainUIBase>(CreateWidget(GetWorld(), mMainUIClass));
		if (IsValid(mMainUI))
		{
			mMainUI->AddToViewport();
		}
	}
}
