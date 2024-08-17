// Copyright Stevan Kostic

#include "DitherTickGameMode.h"

#include "DitherTickPlayerController.h"
#include "GameFramework/HUD.h"
#include "UObject/ConstructorHelpers.h"


ADitherTickGameMode::ADitherTickGameMode()
{
	static ConstructorHelpers::FClassFinder<AHUD> HUD(TEXT("/Script/Engine.Blueprint'/Game/BP_HUD'"));
	if (HUD.Succeeded())
	{
		HUDClass = HUD.Class;
	}

	PlayerControllerClass = ADitherTickPlayerController::StaticClass();
}