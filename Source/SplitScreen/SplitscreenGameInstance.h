// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SplitscreenGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API USplitscreenGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	public:
	USplitscreenGameInstance();
	virtual void Init() override;

};
