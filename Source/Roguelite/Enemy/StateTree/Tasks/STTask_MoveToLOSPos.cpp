// Fill out your copyright notice in the Description page of Project Settings.


#include "STTask_MoveToLOSPos.h"

#include "NavigationSystem.h"
#include "Components/CapsuleComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Roguelite/PC/PlayerCharacter.h"
#include "Roguelite/Room/EncounterManager.h"


USTTask_MoveToLOSPos::USTTask_MoveToLOSPos(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	bShouldStateChangeOnReselect = true;
	bShouldCallTick = true;
}

EStateTreeRunStatus USTTask_MoveToLOSPos::EnterState(FStateTreeExecutionContext& Context,
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
	if (not AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("AIController ptr error"));
		return RunStatus = EStateTreeRunStatus::Failed;
	}
	
	UWorld* World = GetWorld();
	if (not World)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cant get world"))
		return RunStatus = EStateTreeRunStatus::Failed;

	}
	
	// Gets the NavMesh
	const UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(World);
	if (not NavSys)
	{
		UE_LOG(LogTemp, Error, TEXT("NavSys error"));
		return RunStatus = EStateTreeRunStatus::Failed;
	}
	
	TObjectPtr<AEncounterManager> EncounterManager = Enemy -> EncounterManager;
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
	
	
	
	// Prepare collision params
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Enemy);
	QueryParams.bTraceComplex = false;
	QueryParams.bReturnPhysicalMaterial = false;
	
	
	const FVector TraceEnd = FVector(
				PlayerCharacter -> GetActorLocation().X, 
				PlayerCharacter -> GetActorLocation().Y, 
			PlayerCharacter -> GetActorLocation().Z + PlayerCharacter -> GetCapsuleComponent() -> GetScaledCapsuleHalfHeight()
			);
	
	bool bFailedHit = false;
	for (int32 AttemptNumber = 0; AttemptNumber < AttemptsToCheck; AttemptNumber++)
	{
		FNavLocation DestinationData; // The data location itself
		bool bIsPointValid = false;
		if(bFailedHit)
		{
			bIsPointValid = NavSys -> GetRandomReachablePointInRadius(PlayerCharacter -> GetActorLocation(), MaxCheckDistance*3, DestinationData);
		}
		else
		{
			bIsPointValid = NavSys -> GetRandomReachablePointInRadius(Enemy -> GetActorLocation(), MaxCheckDistance, DestinationData);
		}
		
		// Checks if the point is valid or not
		if (not bIsPointValid)
		{
			UE_LOG(LogTemp, Error, TEXT("Point from NavMesh is invalid"));
			continue;
		}
	
		const FVector TraceStart = FVector(DestinationData.Location.X, DestinationData.Location.Y, DestinationData.Location.Z + Enemy -> GetCapsuleComponent() -> GetScaledCapsuleHalfHeight())  ;
		
		// Perform trace
		FHitResult Hit;
		const bool bDidHit = World -> LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannel, QueryParams);
		
		if (not bDidHit)
		{
			DrawDebugLine(World, TraceStart, TraceEnd, FColor::Red, false, 1.0f, 0, 0.5f);
			bFailedHit = true;
			continue;
		}
		
		AActor* HitActor = Hit.GetActor();
		if (Cast<APlayerCharacter>(HitActor))
		{
			if (FVector::Distance(TraceEnd, TraceStart) < MinimumRange)
			{
				DrawDebugLine(World, TraceStart, TraceEnd, FColor::Green, false, 2.0f, 0, 0.5f);
				bFailedHit = true;
				continue;
			}
			
			DrawDebugLine(World, TraceStart, TraceEnd, FColor::Purple, false, 2.0f, 0, 0.5f);
			AIController -> MoveToLocation(DestinationData.Location);
			return (RunStatus = EStateTreeRunStatus::Running);
		}
		bFailedHit = true;
	}
	
	
	return (RunStatus = EStateTreeRunStatus::Failed);
}

EStateTreeRunStatus USTTask_MoveToLOSPos::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	if (not AIController)
	{
		return RunStatus = EStateTreeRunStatus::Failed;
	}
	if (AIController -> GetMoveStatus() == EPathFollowingStatus::Type::Idle)
	{
		return (RunStatus = EStateTreeRunStatus::Succeeded);
	}
	
	return (RunStatus = EStateTreeRunStatus::Running);
}
