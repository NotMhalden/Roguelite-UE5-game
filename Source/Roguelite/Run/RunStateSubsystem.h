// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Roguelite/Augments/AugmentDataAsset.h"
#include "Roguelite/PC/PlayerCharacter.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UObject/SoftObjectPtr.h"
#include "RunStateSubsystem.generated.h"



/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="Hex RunState"))
class ROGUELITE_API URunStateSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	URunStateSubsystem();
	
public:
	void PlayerClearedRoom();
	
	void OnRunFinished();
	void OnPlayerDeath();
	void ResetRun();
	
	void SaveDataFromPlayer(APlayerCharacter* PlayerCharacter);
	void SetDataToPlayer(APlayerCharacter* PlayerCharacter);
	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Run")
	int32 RoomsCleared = 0;
	
	
protected:
	/*
	 * Player stats!
	 * These are the ones that will be carried across rooms. Run data as you will
	 */
	FRunStatePlayerVariables RunStatePlayerVariables;
	
};
