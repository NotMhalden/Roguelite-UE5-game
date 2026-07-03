// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "EnemyDelegates.h"
#include "NavigationSystem.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent() -> InitCapsuleSize(45.0f, 90.0f);
	GetCapsuleComponent() -> SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	GetMesh() -> SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetCharacterMovement() -> MaxStepHeight = 45.0f;
	GetCharacterMovement() -> GravityScale = 6.f;
	
	
	
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
	
	
	
	FNavLocation ClosestNavMeshLocation;
	bool bCouldProject = NavSys -> ProjectPointToNavigation(GetActorLocation(), ClosestNavMeshLocation);
	if (not bCouldProject)
		return;
	
	FVector EnemyLocation = FVector(
		GetActorLocation().X, 
		GetActorLocation().Y, 
		GetActorLocation().Z -  GetCapsuleComponent() -> GetScaledCapsuleHalfHeight());
	
	float DistanceToNavMesh = (ClosestNavMeshLocation.Location - EnemyLocation).Length();
	
	if (DistanceToNavMesh < GetCapsuleComponent() -> GetScaledCapsuleRadius())
		return;
	
	SetActorLocation(ClosestNavMeshLocation.Location + FVector(0.f, 0.f, GetCapsuleComponent() -> GetScaledCapsuleHalfHeight()));
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
	}
	Destroy();
}

