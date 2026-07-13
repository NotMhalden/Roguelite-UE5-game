// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatManager.h"

#include "Roguelite/Enemy/EnemyDelegates.h"

UCombatManager::UCombatManager()
{
	OnEnemyAttackFinished.AddUObject(this, &UCombatManager::EnemyFinishedAttack);
}



bool UCombatManager::RequestAttack(TWeakObjectPtr<AEnemyCharacter> EnemyRequester, int32 AttackTokenCost)
{
	if (not EnemyRequester.Get() or EnemyRequester.IsStale())
		return false;
	
	if (CurrentAttackers.Contains(EnemyRequester))
		RemoveEnemyAsAttacker(EnemyRequester);
		
	/* 
	 * Add better token calculations later.
	 * Current implementation works fine for now
	*/
	if (RegisterEnemyAsAttacker(EnemyRequester, AttackTokenCost))
		return true;
	
	return false;
}

bool UCombatManager::IsAttackPossible(int32 AttackTokenCost)
{
	if (AvailableAttackTokens <= 0 or AvailableAttackTokens < AttackTokenCost)
		return false;
	
	return true;
}

int32 UCombatManager::GetAmountOfAttackers()
{
	return CurrentAttackers.Num();
}


bool UCombatManager::UseTokens(int32 Tokens)
{
	if (AvailableAttackTokens <= 0 or AvailableAttackTokens < Tokens)
		return false;
	
	AvailableAttackTokens -= Tokens;
	return true;
}

bool UCombatManager::AddTokens(int32 Tokens)
{
	if (AvailableAttackTokens + Tokens > TotalAttackTokens)
		return false;
	
	AvailableAttackTokens += Tokens;
	
	return true;
}


bool UCombatManager::RegisterEnemyAsAttacker(TWeakObjectPtr<AEnemyCharacter> NewAttacker, int32 TokensToUse)
{
	if (not NewAttacker.Get() or NewAttacker.IsStale())
		return false;
	
	if (not UseTokens(TokensToUse))
		return false;
	
	CurrentAttackers.Add(NewAttacker, TokensToUse);
	return true;
}

bool UCombatManager::RemoveEnemyAsAttacker(TWeakObjectPtr<AEnemyCharacter> AttackerToRemove)
{
	if (not AttackerToRemove.Get() or AttackerToRemove.IsStale())
		return false;
	
	if (CurrentAttackers.IsEmpty())
		return false;
	
	if (not CurrentAttackers.Contains(AttackerToRemove))
		return false;
	
	if (not AddTokens(CurrentAttackers[AttackerToRemove]))
		return false;
	
	CurrentAttackers.Remove(AttackerToRemove);
	return true;
}



void UCombatManager::EnemyFinishedAttack(TWeakObjectPtr<AEnemyCharacter> FinishedAttacker)
{
	RemoveEnemyAsAttacker(FinishedAttacker);
}
