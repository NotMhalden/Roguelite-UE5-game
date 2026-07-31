// Fill out your copyright notice in the Description page of Project Settings.


#include "RunStateSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Roguelite/PC/PlayerDelegates.h"

URunStateSubsystem::URunStateSubsystem()
{
	SetRunStatePlayerVariablesDelegate.AddUObject(this, &URunStateSubsystem::SetDataToPlayer);
	SaveRunStatePlayerVariablesDelegate.AddUObject(this, &URunStateSubsystem::SaveDataFromPlayer);
}



void URunStateSubsystem::PlayerClearedRoom()
{
	RoomsCleared++;
	UE_LOG(LogTemp, Warning, TEXT("Rooms cleared: %d"), RoomsCleared);
}



void URunStateSubsystem::OnRunFinished()
{
	ResetRun();
}


void URunStateSubsystem::OnPlayerDeath()
{
	ResetRun();
}


void URunStateSubsystem::ResetRun()
{
	RoomsCleared = 0;
	
	/* Player stat reset 
	 * Change it to be savefile data later, once that's done
	 * As some meta-upgrades might change health
	 * Or some challenge or run thing might change it
	 */
	
	RunStatePlayerVariables = FRunStatePlayerVariables();
	
 	UGameplayStatics::OpenLevel(this, FName(TEXT("/Game/Roguelite/Level/Level_Hub")));
}

void URunStateSubsystem::SaveDataFromPlayer(APlayerCharacter* PlayerCharacter)
{
	RunStatePlayerVariables.MaxHealth = PlayerCharacter -> GetMaxHealth();
	RunStatePlayerVariables.CurrentHealth = PlayerCharacter -> GetHealth();
	RunStatePlayerVariables.MantlingTime = PlayerCharacter -> GetMantlingTime();
	RunStatePlayerVariables.ActiveAugments = PlayerCharacter -> ActiveAugments;
}

void URunStateSubsystem::SetDataToPlayer(APlayerCharacter* PlayerCharacter)
{
	PlayerCharacter -> SetHealth(RunStatePlayerVariables.CurrentHealth);
	PlayerCharacter -> SetMaxHealth(RunStatePlayerVariables.MaxHealth);
	PlayerCharacter -> SetMantlingTime(RunStatePlayerVariables.MantlingTime);
	PlayerCharacter -> ActiveAugments = RunStatePlayerVariables.ActiveAugments;
}