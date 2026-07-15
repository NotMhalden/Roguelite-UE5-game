// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvQueryContext_Enemies.h"

#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Roguelite/Enemy/EnemyCharacter.h"
#include "Roguelite/Room/EncounterManager.h"

void UEnvQueryContext_Enemies::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	AEnemyCharacter* EnemyQuerier = Cast<AEnemyCharacter>(QueryInstance.Owner.Get());
	if (not EnemyQuerier)
		return;
	
	TArray<AActor*> AllActors;
	if (not EnemyQuerier -> EncounterManager.Get())
		return;
	
	AllActors.Append(EnemyQuerier -> EncounterManager -> Enemies);
	if (AllActors.IsEmpty())
		return;
	
	AllActors.Remove(EnemyQuerier);
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, AllActors);
}
