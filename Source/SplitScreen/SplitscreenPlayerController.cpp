#include "SplitscreenPlayerController.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Net/UnrealNetwork.h"
#include "SplitScreenCharacter.h"
#include "SplitScreen.h"
#include "SplitscreenHUD.h"
#include "playerSplitscreenWidget.h"

ASplitscreenPlayerController::ASplitscreenPlayerController()
{
    SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
    SceneCaptureComponent->SetupAttachment(RootComponent);
}

// PlayerController에서 Camera Location과 Rotation을 설정하기 위한 OtherPlayer 변수를 설정하는 함수
void ASplitscreenPlayerController::SetOtherPlayer()
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* OtherPlayerController = It->Get();

        if (OtherPlayerController && OtherPlayerController != this)
        {
            ASplitScreenCharacter* OtherPawn = Cast< ASplitScreenCharacter>(OtherPlayerController->GetPawn());
            OtherPlayer = OtherPawn;
        }
    }
}

void ASplitscreenPlayerController::BeginPlay()
{
    Super::BeginPlay();

    FInputModeGameOnly GameOnlyInputMode;
    SetInputMode(GameOnlyInputMode);
}


// OtherPlayer의 카메라 위치와 회전 값을 가지고 와서 변수에 값을 업데이트한다.
void ASplitscreenPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // OtherPlayer의 카메라 위치와 회전 값을 가지고 와서 변수에 값을 설정한다.
    if (OtherPlayer)
    {
        const FVector OtherPawnCameraLocation = OtherPlayer->GetCameraLocation();
        const FRotator OtherPawnCameraRotation = OtherPlayer->GetCameraRotation();

        SetPlayerCameraLocationAndRotation(OtherPawnCameraLocation, OtherPawnCameraRotation);
    }

    // SceneCaptureComponent의 위치를 업데이트한다.
    UpdateSceneCapture();
}

void ASplitscreenPlayerController::SetPlayerCameraLocationAndRotation(FVector Location, FRotator Rotation)
{
    CameraLocation = Location;
    CameraRotation = Rotation;
}

void ASplitscreenPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ASplitscreenPlayerController, CameraLocation);
    DOREPLIFETIME(ASplitscreenPlayerController, CameraRotation);
}

void ASplitscreenPlayerController::UpdateSceneCapture()
{
    if (IsLocalController() && SceneCaptureComponent)
    {
        SceneCaptureComponent->SetWorldLocationAndRotation(CameraLocation, CameraRotation);
    }
}

// 상대방의 화면을 띄우는 오른쪽의 viewport에 RenderTarge에 저장한 후, WIdget의 Texture를 넘겨준다.
void ASplitscreenPlayerController::SetRenderTargetWidget()
{
    ensure(SceneCaptureComponent);

    RenderTarget = NewObject<UTextureRenderTarget2D>(this, UTextureRenderTarget2D::StaticClass());
        
    if (RenderTarget) 
    {
        RenderTarget->InitAutoFormat(WIDTH, HEIGHT);
        RenderTarget->ClearColor = FLinearColor::Black;
        RenderTarget->UpdateResourceImmediate(true);
    
        if (ASplitscreenHUD* HUD = GetHUD<ASplitscreenHUD>())
        {
            if (UplayerSplitscreenWidget* Widget = HUD->GetWidget())
            {
                Widget->SetPlayerRenderTarget(RenderTarget);
            }
        }
        SceneCaptureComponent->TextureTarget = RenderTarget;
    }

    SceneCaptureComponent->bCaptureEveryFrame = true;
    SceneCaptureComponent->bCaptureOnMovement = true;
    SceneCaptureComponent->ShowFlags.SetPostProcessing(true);
}