// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvQueryContext_Player.h"

#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Roguelite/PC/PlayerCharacter.h"

void UEnvQueryContext_Player::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	ACharacter* QueryCharacter = UGameplayStatics::GetPlayerCharacter(QueryInstance.Owner.Get(), 0);
	if (not QueryCharacter)
		return;
	
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(QueryCharacter);
	if (not PlayerCharacter)
		return;
	
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, PlayerCharacter);
}
