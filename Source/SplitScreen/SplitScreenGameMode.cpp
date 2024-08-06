// Copyright Epic Games, Inc. All Rights Reserved.

#include "SplitScreenGameMode.h"
#include "SplitScreenCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "YMGameViewportClient.h"
#include "SplitscreenGameState.h"
#include "SplitscreenHUD.h"

ASplitScreenGameMode::ASplitScreenGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/SplitScreen.SplitscreenPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

	GameStateClass = ASplitscreenGameState::StaticClass();
}


void ASplitScreenGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer != nullptr) 
	{
		if (ASplitscreenGameState* SplitscreenGameState = GetGameState<ASplitscreenGameState>())
		{
			SplitscreenGameState->AddPlayer();
		}
	}
}

void ASplitScreenGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	if (ASplitscreenGameState* SplitscreenGameState = GetGameState<ASplitscreenGameState>())
	{
		SplitscreenGameState->RemovePlayer();
	}
}