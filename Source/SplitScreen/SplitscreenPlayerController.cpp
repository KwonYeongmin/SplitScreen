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

// PlayerController���� Camera Location�� Rotation�� �����ϱ� ���� OtherPlayer ������ �����ϴ� �Լ�
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


// OtherPlayer�� ī�޶� ��ġ�� ȸ�� ���� ������ �ͼ� ������ ���� ������Ʈ�Ѵ�.
void ASplitscreenPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // OtherPlayer�� ī�޶� ��ġ�� ȸ�� ���� ������ �ͼ� ������ ���� �����Ѵ�.
    if (OtherPlayer)
    {
        const FVector OtherPawnCameraLocation = OtherPlayer->GetCameraLocation();
        const FRotator OtherPawnCameraRotation = OtherPlayer->GetCameraRotation();

        SetPlayerCameraLocationAndRotation(OtherPawnCameraLocation, OtherPawnCameraRotation);
    }

    // SceneCaptureComponent�� ��ġ�� ������Ʈ�Ѵ�.
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

// ������ ȭ���� ���� �������� viewport�� RenderTarge�� ������ ��, WIdget�� Texture�� �Ѱ��ش�.
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