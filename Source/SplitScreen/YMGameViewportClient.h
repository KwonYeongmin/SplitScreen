// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "YMGameViewportClient.generated.h"


UENUM(BlueprintType)
namespace EYMSplitScreenType
{
    enum Type
    {
        None,
        TwoPlayer = ESplitScreenType::SplitTypeCount,
        SplitTypeCount
    };
}

struct FNetModeDebugging
{
    FString NetModeInfo;
    FString LocalNetModeInfo;
    FString RemoteNetModeInfo;

    FNetModeDebugging() : NetModeInfo(""), LocalNetModeInfo(""), RemoteNetModeInfo("") {  }
    FNetModeDebugging(FString NewNetModeInfo, FString NewLocalNetModeInfo, FString NewRemoteNetModeInfoo) 
        : NetModeInfo(NewNetModeInfo), LocalNetModeInfo(NewLocalNetModeInfo), RemoteNetModeInfo(NewRemoteNetModeInfoo) {  }
};

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API UYMGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
	
public:
	UYMGameViewportClient(const FObjectInitializer& ObjectInitializer);
	virtual void UpdateActiveSplitscreenType() override;

private:
    FNetModeDebugging GetNetModeInfo() const;
   
};
