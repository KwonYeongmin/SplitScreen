// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SplitScreenGameMode.generated.h"

UCLASS(minimalapi)
class ASplitScreenGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASplitScreenGameMode();
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
};



