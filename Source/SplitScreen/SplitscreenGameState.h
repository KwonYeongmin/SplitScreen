// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SplitscreenGameState.generated.h"

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API ASplitscreenGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ASplitscreenGameState();

protected:
	virtual void PostInitializeComponents() override;

public:
	FORCEINLINE int32 GetPlayerNum() const { return PlayerNum; }
	void AddPlayer() ;
	void RemovePlayer();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION()
	void OnRep_PlayerNum();
	void ChangePlayerNum();

private:
	UPROPERTY(ReplicatedUsing = OnRep_PlayerNum, EditAnywhere, Category = "Clients")
	int32 PlayerNum = 0;

	
};
