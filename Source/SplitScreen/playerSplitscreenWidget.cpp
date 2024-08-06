#include "playerSplitscreenWidget.h"
#include "Components/Image.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Slate/SlateBrushAsset.h"
#include "Styling/SlateBrush.h"

UplayerSplitscreenWidget::UplayerSplitscreenWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    ConstructorHelpers::FObjectFinder<UMaterialInstance> ScreenMaterialRef
    (TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Material/MI_RenderTarget.MI_RenderTarget'"));

    if (ScreenMaterialRef.Succeeded())
    {
        ScreenMaterialInstance = ScreenMaterialRef.Object;
    }
}

void UplayerSplitscreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UplayerSplitscreenWidget::SetPlayerRenderTarget(UTextureRenderTarget2D* RenderTarget)
{
	PlayerRenderTarget = RenderTarget;
}

void UplayerSplitscreenWidget::SetImage()
{
    if (PlayerScreenImage && PlayerRenderTarget)
    {
        UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(ScreenMaterialInstance, this);
        if (DynMaterial)
        {
            DynMaterial->SetTextureParameterValue(FName("TextureParameter"), PlayerRenderTarget);
            PlayerScreenImage->SetBrushFromMaterial(DynMaterial);
        }
    }
}