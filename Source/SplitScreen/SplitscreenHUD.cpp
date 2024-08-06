#include "SplitscreenHUD.h"
#include "Blueprint/UserWidget.h"
#include "playerSplitscreenWidget.h"
#include "SplitscreenPlayerController.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "SplitScreen.h"

ASplitscreenHUD::ASplitscreenHUD() 
{
    static ConstructorHelpers::FClassFinder<UplayerSplitscreenWidget> HpUIWidgetClassRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BP/BP_SplitScreenWidget.BP_SplitScreenWidget_C'"));
    if (HpUIWidgetClassRef.Class)
    {
        PlayerScreenWidgetClass = HpUIWidgetClassRef.Class;
    }
}

void ASplitscreenHUD::BeginPlay()
{
    Super::BeginPlay();

    ASplitscreenPlayerController* PC = Cast<ASplitscreenPlayerController>(GetOwningPlayerController());

    if(PC == nullptr)
    {
        return;
    }

    if (PlayerScreenWidgetClass)
    {
        PlayerScreenWidget = CreateWidget<UplayerSplitscreenWidget>(GetWorld(), PlayerScreenWidgetClass, TEXT("PlayerScreen"));
       
        if (PlayerScreenWidget)
        {
            PlayerScreenWidget->AddToViewport();
            PC->SetRenderTargetWidget();
            PlayerScreenWidget->SetImage();
        }
    }
}
