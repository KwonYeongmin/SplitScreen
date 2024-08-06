// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "playerSplitscreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API UplayerSplitscreenWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UplayerSplitscreenWidget(const FObjectInitializer& ObjectInitializer);
	void SetPlayerRenderTarget(UTextureRenderTarget2D* RenderTarget);
	void SetImage();

protected:
	virtual void NativeConstruct() override;
	
private:
	TObjectPtr<UMaterialInstance>  ScreenMaterialInstance;

	UPROPERTY(EditAnywhere, Category = "UI")
	TObjectPtr<UTextureRenderTarget2D> PlayerRenderTarget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> PlayerScreenImage;

	UPROPERTY(EditAnywhere, Category = "UI")
	TObjectPtr<UTexture> TestTexture2D;
};
