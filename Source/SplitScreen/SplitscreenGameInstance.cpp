
#include "SplitscreenGameInstance.h"
#include "YMGameViewportClient.h"

USplitscreenGameInstance::USplitscreenGameInstance()
{

}

void USplitscreenGameInstance::Init()
{
	Super::Init();
	if (GEngine && GEngine->GameViewport)
	{
		UYMGameViewportClient* ViewportClient = Cast<UYMGameViewportClient>(GEngine->GameViewport);
		if (ViewportClient)
		{
			ViewportClient->UpdateActiveSplitscreenType();
		}
	}
}
