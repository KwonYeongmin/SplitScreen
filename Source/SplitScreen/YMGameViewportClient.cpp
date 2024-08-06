
#include "YMGameViewportClient.h"
#include "YMSreensplitGameMode.h"
#include "SplitscreenGameState.h"
#include "SplitScreen.h"

UYMGameViewportClient::UYMGameViewportClient(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
    // Resize SplitscreenInfo to fit our custom config
    SplitscreenInfo.SetNum(EYMSplitScreenType::SplitTypeCount, false);

    // Fill the custom config
    SplitscreenInfo[EYMSplitScreenType::TwoPlayer].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 1.0f, 0.0f, 0.0f)); //1
    SplitscreenInfo[EYMSplitScreenType::TwoPlayer].PlayerData.Add(FPerPlayerSplitscreenData(0.5f, 1.0f, 0.5f, 0.0f)); //2
}

void UYMGameViewportClient::UpdateActiveSplitscreenType()
{
    if (ASplitscreenGameState* SplitscreenGameState =  GetWorld()->GetGameState<ASplitscreenGameState>())
    {
        const  int32 NumberOfPlayers = SplitscreenGameState->GetPlayerNum();
      
        if (NumberOfPlayers == 2)
        {
            ActiveSplitscreenType = static_cast<ESplitScreenType::Type>(EYMSplitScreenType::TwoPlayer);
        }
        else
        {
            Super::UpdateActiveSplitscreenType();
        }
    }
}

FNetModeDebugging UYMGameViewportClient::GetNetModeInfo() const
{
    const FString NetModeInfo =
        (GetWorld()->GetNetMode() == ENetMode::NM_Client) ? *FString::Printf(TEXT("CLIENT%d"), GPlayInEditorID) : ((GetWorld()->GetNetMode() == ENetMode::NM_Standalone) ? TEXT("STANDALONE") : TEXT("SERVER"));

    FString LocalNetModeInfo;
    FString RemoteNetModeInfo;

    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        LocalNetModeInfo = UEnum::GetValueAsString(TEXT("Engine.ENetRole"), PC->GetLocalRole());
        RemoteNetModeInfo = UEnum::GetValueAsString(TEXT("Engine.ENetRole"), PC->GetRemoteRole());
    }
    else
    {
        LocalNetModeInfo = TEXT("NO_PLAYER_CONTROLLER");
        RemoteNetModeInfo = TEXT("NO_PLAYER_CONTROLLER");
    }

    return FNetModeDebugging(NetModeInfo, LocalNetModeInfo, RemoteNetModeInfo);
}
