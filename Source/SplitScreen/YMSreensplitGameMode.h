// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "YMSreensplitGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API AYMSreensplitGameMode : public AGameMode
{
	GENERATED_BODY()
	
	public:
		AYMSreensplitGameMode();
		virtual void PostLogin(APlayerController* NewPlayer) override;
};
