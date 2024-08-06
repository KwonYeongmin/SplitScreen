// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SplitscreenHUD.generated.h"

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API ASplitscreenHUD : public AHUD
{
	GENERATED_BODY()
	
public:
    ASplitscreenHUD();
    virtual void BeginPlay() override;
    class UplayerSplitscreenWidget* GetWidget() const { return PlayerScreenWidget; }

private:
    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<class UUserWidget> PlayerScreenWidgetClass;

    UPROPERTY()
    TObjectPtr<class UplayerSplitscreenWidget> PlayerScreenWidget;
};
