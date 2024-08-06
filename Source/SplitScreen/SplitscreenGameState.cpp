#include "SplitscreenGameState.h"
#include "Net/UnrealNetwork.h"
#include "SplitScreen.h"
#include "YMGameViewportClient.h"

ASplitscreenGameState::ASplitscreenGameState()
{
	PlayerNum = 0;
}

void ASplitscreenGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	bReplicates = true;
}

void ASplitscreenGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASplitscreenGameState, PlayerNum);
}

void ASplitscreenGameState::AddPlayer()
{
	++PlayerNum;
	ChangePlayerNum();
}

void ASplitscreenGameState::RemovePlayer()
{
	--PlayerNum;
	ChangePlayerNum();
}

void ASplitscreenGameState::OnRep_PlayerNum()
{
	ChangePlayerNum();
}

void ASplitscreenGameState::ChangePlayerNum()
{
	// SS_LOG(LogTemp, Warning, TEXT("PlayerNum : %d"), PlayerNum);
}
