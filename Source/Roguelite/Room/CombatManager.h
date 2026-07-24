// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CombatManager.generated.h"

class AEnemyCharacter;






/**
 * 
 */
UCLASS(EditInlineNew)
class ROGUELITE_API UCombatManager : public UObject
{
	GENERATED_BODY()
	
public:
	UCombatManager();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Token", meta=(AllowPrivateAccess))
	int32 TotalAttackTokens = 10;
	UPROPERTY(VisibleAnywhere, Category = "Token", meta=(AllowPrivateAccess))
	int32 AvailableAttackTokens = TotalAttackTokens;
	
	
	TMap< TWeakObjectPtr<AEnemyCharacter>, int32 > CurrentAttackers;

	
public:
	bool RequestAttack(TWeakObjectPtr<AEnemyCharacter> EnemyRequester, int32 AttackTokenCost);
	bool IsAttackPossible(int32 AttackTokenCost);
	
	int32 GetAmountOfAttackers();

protected:
	bool UseTokens(int32 Tokens);
	bool AddTokens(int32 Tokens);
	
	bool RegisterEnemyAsAttacker(TWeakObjectPtr<AEnemyCharacter> NewAttacker, int32 TokensToUse);
	bool RemoveEnemyAsAttacker(TWeakObjectPtr<AEnemyCharacter> AttackerToRemove);
	
	UFUNCTION()
	void EnemyFinishedAttack(TWeakObjectPtr<AEnemyCharacter> FinishedAttacker);
	
};
