// Fill out your copyright notice in the Description page of Project Settings.


#include "STEvaluator_CheckForPlayerUpdate.h"

#include "Roguelite/PC/PlayerCharacter.h"
#include "Roguelite/Room/EncounterManager.h"

void USTEvaluator_CheckForPlayerUpdate::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	Super::Tick(Context, DeltaTime);
	
	TObjectPtr<APlayerCharacter> PlayerCharacter = Enemy ->EncounterManager -> GetPlayerCharacter();
	FVector PlayerPosition = PlayerCharacter -> GetActorLocation();
	
	DistanceToPlayer = FVector::Dist(PlayerPosition, Enemy -> GetActorLocation());
}
