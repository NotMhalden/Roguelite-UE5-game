// Fill out your copyright notice in the Description page of Project Settings.


#include "STTask_MoveToLOSPos.h"

#include "NavigationPath.h"
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
	if (not EnemyController)
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
				PlayerCharacter -> GetActorLocation().Z
			);
	
	
	float BestScore = 0.f;
	FVector BestPosition = FVector(0.f,0.f,0.f);
	
	// Looks AttemptsToCheck times to see if there's a valid place the enemy can be, and see the player
	bool bFailedHit = false;
	for (int32 AttemptNumber = 0; AttemptNumber < AttemptsToCheck; AttemptNumber++)
	{
		FNavLocation DestinationData; // The data location itself
		bool bIsPointValid = false;
		
		if(bFailedHit)
		{
			bIsPointValid = NavSys -> GetRandomReachablePointInRadius(PlayerCharacter -> GetActorLocation(), MaxCheckDistance, DestinationData);
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
				// DrawDebugLine(World, TraceStart, TraceEnd, FColor::Green, false, 2.0f, 0, 0.5f);
				bFailedHit = true;
				continue;
			}

			float PositionScore = 0;
			
			
			// -- Height scoring for position -- 
			
			// Gets the height difference between the possible location and the player's feet
			float HeightGap =
					  DestinationData.Location.Z
					- PlayerCharacter -> GetActorLocation().Z - PlayerCharacter -> GetCapsuleComponent() -> GetScaledCapsuleHalfHeight();
			
			// Finds out how many EEnemyElevationPositioning the Enemy should be compared to the player
			int32 IdealElevation = (int32)Enemy -> CurrentPositioning - (int32)EEnemyElevationPositioning::EEEP_SameLevel;
			
			// Finds the height difference between the possible point, and the ideal point
			float IdealHeight = FMath::Abs(HeightGap - IdealElevation * EncounterManager -> PositioningHeightThreshold);
			
			// Gets the distance between the position and the plateau
			float DistanceFromIdealHeight = FMath::Max(0.f, IdealHeight - EncounterManager -> PositioningHeightPlateau);
			
			// Applies falloff depending on how far the position is from the ideal
			float HeightScoreFalloffFactor = FMath::Pow(0.5f, DistanceFromIdealHeight / EncounterManager -> PositioningHeightThreshold);
			
			// The position gets its scored multiplied by 40 (out of 100). 
			// 30 is the weight for height. 
			// Higher means a position with more correct height matters more
			PositionScore += 40 * HeightScoreFalloffFactor;
			
			// DrawDebugLine(World, TraceStart, TraceEnd, FColor::Cyan, false, 2.0f, 0, 0.5f);
			
			
			
			// -- Distance scoring for position -- 
			FVector2D Position2D = FVector2D(DestinationData.Location.X, DestinationData.Location.Y);
			FVector2D PlayerPosition2D = FVector2D(PlayerCharacter -> GetActorLocation().X, PlayerCharacter -> GetActorLocation().Y);
			
			float PositionFromPlayer = (Position2D - PlayerPosition2D).Length();
			float DistanceFromIdealDistance = FMath::Abs(Enemy -> IdealDistance - PositionFromPlayer);
			float DistanceFromPlateau = FMath::Max(0.f, DistanceFromIdealDistance - Enemy -> DistancePlateau);
			float DistanceScoreFalloffFactor = FMath::Pow(0.5f, DistanceFromPlateau / Enemy -> DistanceFalloff);
			
			PositionScore += 40 * DistanceScoreFalloffFactor;
			
			
			
			
			// -- Travel distance scoring for position -- 
			float TravelDistance = FVector::Dist2D(DestinationData.Location, Enemy -> GetActorLocation());
			float TravelDistanceScoreFalloffFactor = FMath::Pow(0.5f, TravelDistance / Enemy -> TravelDistanceFalloff);
			
			PositionScore += 20 * TravelDistanceScoreFalloffFactor;
			
			
			// -- Player distance to position scoring for position -- 
			float PlayerDistanceToPath = FMath::PointDistToSegment(
				PlayerCharacter -> GetActorLocation(),
				Enemy -> GetActorLocation(),
				DestinationData.Location);
			float PlayerTimeToPathFalloffFactor = 1.f - FMath::Pow(0.5f, PlayerDistanceToPath / Enemy -> PlayerToPathDistanceFalloff);
			
			if (PlayerTimeToPathFalloffFactor <= 0.3f)
			{
				TObjectPtr<UNavigationPath> Path = NavSys -> FindPathToLocationSynchronously(World, Enemy -> GetActorLocation(), DestinationData.Location);
				float MinDistance = TNumericLimits<float>::Max();;
				if (not Path)
				{
					continue;
				}
				if (Path -> IsPartial())
				{
					continue;
				}
				for (int PathPointIndex = 0; PathPointIndex+1 < Path -> PathPoints.Num(); PathPointIndex++)
				{
					/*
					DrawDebugLine(World, 
						Path -> PathPoints[PathPointIndex], 
						Path -> PathPoints[PathPointIndex+1], 
						FColor::Red, false, 2.0f, 0, 0.5f);
					*/
					
					
					MinDistance = FMath::Min(MinDistance, FMath::PointDistToSegment(
														PlayerCharacter -> GetActorLocation(), 
														Path -> PathPoints[PathPointIndex],
														Path -> PathPoints[PathPointIndex+1]));
				}
				PlayerTimeToPathFalloffFactor = 1.f - FMath::Pow(0.4f, MinDistance / Enemy -> PlayerToPathDistanceFalloff);
				PositionScore *= PlayerTimeToPathFalloffFactor;
				
			}
			else
			{
				// DrawDebugLine(World, TraceStart, TraceEnd, FColor::Emerald, false, 2.0f, 0, 0.5f);
				PositionScore *= PlayerTimeToPathFalloffFactor;
			}
			
			
			
			
			
			if (PositionScore >= BestScore)
			{
				BestScore = PositionScore;
				BestPosition = DestinationData.Location;
			}
			bFailedHit = false;
			continue;
		}
		bFailedHit = true;
	}
	
	
	if (not BestScore)
	{
		return (RunStatus = EStateTreeRunStatus::Failed);
	}
	if (BestPosition.IsZero())
	{
		return (RunStatus = EStateTreeRunStatus::Failed);
	}
	
	
	// DrawDebugLine(World, BestPosition, TraceEnd, FColor::Purple, false, 0.5f, 0, 0.5f);
	EnemyController -> MoveToLocation(BestPosition);
	
	return (RunStatus = EStateTreeRunStatus::Running);
}



EStateTreeRunStatus USTTask_MoveToLOSPos::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
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
