// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "AIController.h"
#include "EnemyController.h"
#include "EnemyDelegates.h"
#include "NavigationSystem.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Roguelite/Room/EncounterManager.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	TriggerBox -> SetupAttachment(GetMesh());
	
	
	GetCapsuleComponent() -> InitCapsuleSize(45.0f, 90.0f);
	GetCapsuleComponent() -> SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetCapsuleComponent() -> SetCollisionObjectType(ECC_GameTraceChannel1);
	GetCapsuleComponent() -> SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
	
	GetMesh() -> SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetCharacterMovement() -> MaxStepHeight = 45.0f;
	GetCharacterMovement() -> GravityScale = 9.f;
	
	
	
	TArray<EEnemyElevationPositioning> EnemyPositionKeys;
	EnemyPositioningNurtureChance.GetKeys(EnemyPositionKeys);
	
	const UEnum* EnemyPositionEnum = StaticEnum<EEnemyElevationPositioning>();
	for (int32 EnumIndex = 0; EnumIndex < EnemyPositionEnum -> NumEnums() -1; EnumIndex++)
	{
		auto EnumValue = StaticCast<EEnemyElevationPositioning>(EnemyPositionEnum -> GetValueByIndex(EnumIndex));
		if (EnemyPositionKeys.IsEmpty())
		{
			EnemyPositioningNurtureChance.Add(EnumValue, 0);
			continue;
		}
		if (not EnemyPositionKeys.Contains(EnumValue))
		{
			EnemyPositioningNurtureChance.Add(EnumValue, 0);
			continue;
		}
	}
}


// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(SafetyNetTimerHandle, this, &AEnemyCharacter::MovementSafetyNet, 2.f, false);
}


// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	
	if (ActiveJumpLink.IsValid())
	{
		ActiveJumpLink -> ResumePathFollowing(this);
		ActiveJumpLink.Reset();
	}
}

void AEnemyCharacter::MovementSafetyNet()
{
	GetWorldTimerManager().SetTimer(SafetyNetTimerHandle, this, &AEnemyCharacter::MovementSafetyNet, 2.f, false);
	
	UWorld* World = GetWorld();
	if (not World)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cant get world"))
		return;

	}
	
	// Gets the NavMesh
	const UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(World);
	if (not NavSys)
	{
		UE_LOG(LogTemp, Error, TEXT("NavSys error"));
		return;
	}
	
	const AEnemyController* EnemyController = Cast<AEnemyController>(GetController());
	if (not EnemyController)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemy Controller error"));
		return;
	}
	
	/*
	UE_LOG(LogTemp, Warning, TEXT("status=%d  jumpLinkValid=%d  stuck=%.1f"),
		(int)EnemyController->GetMoveStatus(), ActiveJumpLink.IsValid(), TimeEnemyStuck);
	*/
	
	if (EnemyController -> GetMoveStatus() == EPathFollowingStatus::Type::Idle)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Stuck"));
		const float DistanceMoved = FVector::Dist2D(GetActorLocation(), LastKnownLocation);
		if (DistanceMoved < SafetyNetActivationDistanceThreshold)
		{
			TimeEnemyStuck += 2.f;
		}
		else
		{
			TimeEnemyStuck = 0.f;
		}
	}
	else
	{
		TimeEnemyStuck = 0.f;
	}
	LastKnownLocation = GetActorLocation();
	
	if (TimeEnemyStuck >= 2.5f)
	{
		if (ActiveJumpLink.IsValid()) 
			return;
		
		
		
		// UE_LOG(LogTemp, Warning, TEXT("Starting to nudge"));
		FNavLocation ClosestNavMeshLocation;
		bool bFoundPoint = NavSys -> ProjectPointToNavigation(GetActorLocation(), ClosestNavMeshLocation, FVector(500.f, 500.f, 500.f));
		
		UE_LOG(LogTemp, Warning, TEXT("Closest NavMesh Location:  X: %f		Y: %f		Z: %f"),
			ClosestNavMeshLocation.Location.X, ClosestNavMeshLocation.Location.Y, ClosestNavMeshLocation.Location.Z);
		
		if (not bFoundPoint)
			return;
		
		FVector DistanceToNavMesh = ClosestNavMeshLocation.Location - LastKnownLocation;
		DistanceToNavMesh.Z = 0.f;
		UE_LOG( LogTemp, Warning, TEXT("Distance To Navmesh SizeSquared: %f"), DistanceToNavMesh.SizeSquared() )
		UE_LOG( LogTemp, Warning, TEXT("Squared capsule radius: %f"), FMath::Square(GetCapsuleComponent() -> GetScaledCapsuleRadius()) )
		
		if ( DistanceToNavMesh.SizeSquared() >= 5.f )
		{
			FVector EnemyNudgeLocation = FVector(
				ClosestNavMeshLocation.Location.X, 
				ClosestNavMeshLocation.Location.Y, 
				ClosestNavMeshLocation.Location.Z + GetCapsuleComponent() -> GetScaledCapsuleHalfHeight());
			
			// UE_LOG(LogTemp, Warning, TEXT("Nudged"));
			SetActorLocation(EnemyNudgeLocation);
		}
	}
}


void AEnemyCharacter::TakeDamage(int DamageTaken)
{
	Health -= DamageTaken;
	if (Health <= 0)
	{
		Death();
	}
}


void AEnemyCharacter::Death()
{
	if (OnEnemyDeathDelegate.IsBound())
	{
		OnEnemyDeathDelegate.Broadcast();
		
		if (RemoveEnemyAttacker.IsBound())
			RemoveEnemyAttacker.Broadcast(this);
	}
	Destroy();
}

bool AEnemyCharacter::RequestAttack(int32 AttackCost)
{
	if (EncounterManager -> EnemyRequestAttack(this, AttackCost))
		return true;
	return false;
}

void AEnemyCharacter::AttackFinished()
{
	if (RemoveEnemyAttacker.IsBound())
		RemoveEnemyAttacker.Broadcast(this);
}

void AEnemyCharacter::OnPlayerPositionDrift()
{
	if (AEnemyController* EnemyController = Cast<AEnemyController>(GetController()))
	{
		EnemyController -> OnPlayerPositionDrift();
	}
	if (RemoveEnemyAttacker.IsBound())
		RemoveEnemyAttacker.Broadcast(this);
}


void AEnemyCharacter::OnTokenChange()
{
}
