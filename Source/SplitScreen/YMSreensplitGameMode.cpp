#include "YMSreensplitGameMode.h"
#include "SplitScreenCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "YMGameViewportClient.h"
#include "SplitscreenGameState.h"
#include "SplitscreenPlayerController.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PlayerState.h"
#include "SplitScreen.h"

AYMSreensplitGameMode::AYMSreensplitGameMode()
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
	
	static ConstructorHelpers::FClassFinder<AHUD> DefaultHUDRef(TEXT("/Script/SplitScreen.SplitscreenHUD"));
	if (DefaultHUDRef.Class)
	{
		HUDClass = DefaultHUDRef.Class;
	}

	GameStateClass = ASplitscreenGameState::StaticClass();
}

void AYMSreensplitGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer != nullptr)
	{
		if (ASplitscreenGameState* SplitscreenGameState = GetGameState<ASplitscreenGameState>())
		{
			SplitscreenGameState->AddPlayer();
		}
	}

	if (GameState && GameState->PlayerArray.Num() == 2)
	{
		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		{
			APlayerController* PC = It->Get();
			if (PC)
			{
				Cast<ASplitscreenPlayerController>(PC)->SetOtherPlayer();
			}
		}
	}
}
