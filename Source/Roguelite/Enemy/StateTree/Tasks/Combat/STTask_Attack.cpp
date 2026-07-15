// Fill out your copyright notice in the Description page of Project Settings.


#include "STTask_Attack.h"
#include "StateTreeExecutionContext.h"
#include "Roguelite/PC/PlayerCharacter.h"
#include "Roguelite/Room/CombatManager.h"
#include "Roguelite/Room/EncounterManager.h"

USTTask_Attack::USTTask_Attack(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	bShouldStateChangeOnReselect = true;
	bShouldCallTick = true;
}



EStateTreeRunStatus USTTask_Attack::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition)
{
	// Checks if there's an enemy, in case of errors
	if (not Enemy)
	{
		UE_LOG(LogTemp, Error, TEXT("InEnemy ptr error"));
		return RunStatus = EStateTreeRunStatus::Failed;
	}
	
	// Checks if there is an AI Controller
	if (not EnemyController)
	{
		UE_LOG(LogTemp, Error, TEXT("AIController ptr error"));
		return RunStatus = EStateTreeRunStatus::Failed;
	}
	
	
	CurrentAttack = SelectBestAttack();
	
	if (not CurrentAttack)
		return RunStatus = EStateTreeRunStatus::Failed;
	
	if (CurrentAttack and CurrentAttack -> Begin( Enemy.Get(), Enemy->EncounterManager->GetPlayerCharacter() ))
		return RunStatus = EStateTreeRunStatus::Running;
	
	return RunStatus = EStateTreeRunStatus::Running;
}



EStateTreeRunStatus USTTask_Attack::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	if (not CurrentAttack)
		return RunStatus = EStateTreeRunStatus::Failed;
	
	if (CurrentAttack and CurrentAttack -> Tick( Enemy.Get(), Enemy->EncounterManager->GetPlayerCharacter(), DeltaTime ))
	{
		Enemy -> AttackFinished();
		return RunStatus = EStateTreeRunStatus::Succeeded;
	}
	
	return RunStatus = EStateTreeRunStatus::Running;
}



TObjectPtr<UEnemyAttackBase> USTTask_Attack::SelectBestAttack()
{
	if (Enemy -> Attacks.IsEmpty())
		return nullptr;
	if (Enemy -> Attacks.Num() == 1)
	{
		if (Enemy -> EncounterManager -> GetCombatManager() -> IsAttackPossible(Enemy->Attacks[0]->GetTokenCost()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Amount of Attackers: %d"), Enemy -> EncounterManager -> GetCombatManager() ->GetAmountOfAttackers())
			Enemy -> EncounterManager -> GetCombatManager() -> RequestAttack(Enemy, Enemy -> Attacks[0]->GetTokenCost());
			return Enemy -> Attacks[0];
		}
	}

	
	
	TArray<TPair<UEnemyAttackBase*, int32>> PossibleAttacks;
	
	for (UEnemyAttackBase* Attack : Enemy -> Attacks)
	{
		float AttackScore = Attack -> Score( Enemy.Get(), Enemy->EncounterManager->GetPlayerCharacter() );
		
		PossibleAttacks.Add({Attack, AttackScore});
	}
	
	TArray<TPair<UEnemyAttackBase*, int32>> PossibleAttacksSorted;
	
	bool bAttacksIsSorted = false;
	while (not bAttacksIsSorted)
	{
		TPair<UEnemyAttackBase*, int32> LowestScoredAttack = {nullptr, TNumericLimits<int32>::Max()};
		for (TPair PossibleAttack : PossibleAttacks)
		{
			if (PossibleAttack.Value < LowestScoredAttack.Value)
				LowestScoredAttack = PossibleAttack;
			else
				PossibleAttacks.Remove(PossibleAttack);
		}
		PossibleAttacksSorted.Add(LowestScoredAttack);
		PossibleAttacks.Remove(LowestScoredAttack);
		
		if (PossibleAttacks.Num() <= 0)
		{
			bAttacksIsSorted = true;
			break;
		}
	}
	
	for (int AttackIndex = PossibleAttacksSorted.Num() -1; AttackIndex >= 0; AttackIndex--)
	{
		if (PossibleAttacksSorted[AttackIndex].Value == 0)
			continue;
		if (Enemy -> EncounterManager -> GetCombatManager() -> IsAttackPossible(PossibleAttacksSorted[AttackIndex].Value))
		{
			UE_LOG(LogTemp, Warning, TEXT("Amount of Attackers: %d"), Enemy -> EncounterManager -> GetCombatManager() ->GetAmountOfAttackers())
			Enemy -> EncounterManager -> GetCombatManager() -> RequestAttack(Enemy, PossibleAttacksSorted[AttackIndex].Value);
			return PossibleAttacksSorted[AttackIndex].Key;
		}
	}
	return nullptr;
}
