// Fill out your copyright notice in the Description page of Project Settings.


#include "STTask_MoveToRandomLocation.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"



USTTask_MoveToRandomLocation::USTTask_MoveToRandomLocation(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShouldStateChangeOnReselect = true;
	bShouldCallTick = true;
}



EStateTreeRunStatus USTTask_MoveToRandomLocation::EnterState(FStateTreeExecutionContext& Context,
                                                             const FStateTreeTransitionResult& Transition)
{
	// UE_LOG(LogTemp, Warning, TEXT("MoveTask EnterState - new point"));
	RunStatus = EStateTreeRunStatus::Running;
	
	// Checks if there's an enemy, in case of errors
	if (not Enemy)
	{
		UE_LOG(LogTemp, Error, TEXT("InEnemy ptr error"));
		return RunStatus = EStateTreeRunStatus::Failed;
	}
	
	// Checks if there is an AI Controller
	if (not AIController)
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
	
	// Gets a random reachable point within RandomLocationMaxDistance from the InEnemy
	FNavLocation DestinationData; // The data location itself
	bool const bIsPointValid = NavSys -> GetRandomReachablePointInRadius(Enemy -> GetActorLocation(), RandomLocationMaxDistance, DestinationData);

	// Checks if the point is valid or not
	if (not bIsPointValid)
	{
		UE_LOG(LogTemp, Error, TEXT("Point from NavMesh is invalid"));
		return RunStatus = EStateTreeRunStatus::Failed;
	}
	
	// Moves the enemy to the location
	AIController -> MoveToLocation(DestinationData.Location);
	// UE_LOG(LogTemp, Warning, TEXT("MoveTo result: %d"), (int32)AIController->MoveToLocation(DestinationData.Location, 25.f));
	
	return (RunStatus = EStateTreeRunStatus::Running);
}



EStateTreeRunStatus USTTask_MoveToRandomLocation::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("MoveStatus: %d"), (int32)AIController->GetMoveStatus());
	
	if (AIController -> GetMoveStatus() == EPathFollowingStatus::Type::Idle)
	{
		return (RunStatus = EStateTreeRunStatus::Succeeded);
	}
	return (RunStatus = EStateTreeRunStatus::Running);
	
}