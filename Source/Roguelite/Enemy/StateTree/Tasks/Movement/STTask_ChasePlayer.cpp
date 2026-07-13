// Fill out your copyright notice in the Description page of Project Settings.


#include "STTask_ChasePlayer.h"

#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "Roguelite/PC/PlayerCharacter.h"
#include "Roguelite/Room/EncounterManager.h"

USTTask_ChasePlayer::USTTask_ChasePlayer(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	bShouldStateChangeOnReselect = true;
	bShouldCallTick = true;
}


EStateTreeRunStatus USTTask_ChasePlayer::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition)
{
	RunStatus = EStateTreeRunStatus::Running;
	
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
	
	// Gets the NavMesh
	UNavigationSystemV1* const NavSys = UNavigationSystemV1::GetCurrent( GetWorld() );
	if (not NavSys)
	{
		UE_LOG(LogTemp, Error, TEXT("NavSys error"));
		return RunStatus = EStateTreeRunStatus::Failed;
	}
	
	TObjectPtr<AEncounterManager> EncounterManager = Enemy -> EncounterManager.Get();
	if (not EncounterManager)
	{
		UE_LOG(LogTemp, Error, TEXT("EncounterManager ptr error"));
		return RunStatus = EStateTreeRunStatus::Failed;
	}
	
	TObjectPtr<APlayerCharacter> PlayerCharacter = EncounterManager -> GetPlayerCharacter();
	if (not PlayerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerCharacter ptr error"));
		return RunStatus = EStateTreeRunStatus::Failed;
	}
	
	
	EnemyController -> MoveToActor(PlayerCharacter, AcceptanceRadius);
	
	return (RunStatus = EStateTreeRunStatus::Running);

}



EStateTreeRunStatus USTTask_ChasePlayer::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	if (not EnemyController)
	{
		return RunStatus = EStateTreeRunStatus::Failed;
	}
	if (EnemyController -> GetMoveStatus() == EPathFollowingStatus::Type::Idle)
	{
		return (RunStatus = EStateTreeRunStatus::Succeeded);
	}
	return (RunStatus = EStateTreeRunStatus::Running);
}
