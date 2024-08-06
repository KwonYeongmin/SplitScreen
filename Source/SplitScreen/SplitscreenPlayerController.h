#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SplitscreenPlayerController.generated.h"

UCLASS()
class SPLITSCREEN_API ASplitscreenPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ASplitscreenPlayerController();
    FORCEINLINE class USceneCaptureComponent2D* GetUSceneCaptureComponent2D() const { return SceneCaptureComponent; }
    void SetRenderTargetWidget();
    void SetPlayerCameraLocationAndRotation(FVector NewLocation, FRotator NewRotation);
    void SetOtherPlayer();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
    void UpdateSceneCapture();

    TObjectPtr<class ASplitScreenCharacter> OtherPlayer;

    UPROPERTY(Replicated)
    FVector CameraLocation;
    UPROPERTY(Replicated)
    FRotator CameraRotation;

    UPROPERTY(EditAnywhere)
    TObjectPtr<class USceneCaptureComponent2D> SceneCaptureComponent;

    UPROPERTY()
    TObjectPtr<UTextureRenderTarget2D> RenderTarget;
};
