// Fill out your copyright notice in the Description page of Project Settings.


#include "EncounterManager.h"

#include "CombatManager.h"
#include "NavigationSystem.h"
#include "Components/CapsuleComponent.h"
#include "Roguelite/Enemy/EnemyCharacter.h"
#include "Roguelite/Enemy/EnemyController.h"
#include "Roguelite/Enemy/EnemyDelegates.h"
#include "Roguelite/PC/PlayerCharacter.h"


// Sets default values
AEncounterManager::AEncounterManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OnEnemyDeathDelegate.AddUObject(this, &AEncounterManager::OnEnemyDeath);
}

// Called when the game starts or when spawned
void AEncounterManager::BeginPlay()
{
	Super::BeginPlay();
	
	const TObjectPtr<APawn> PlayerPawn = GetWorld() -> GetFirstPlayerController() -> GetPawn();
	if (const TObjectPtr<APlayerCharacter> PlayerCharacterCast = Cast<APlayerCharacter>(PlayerPawn))
	{
		PlayerCharacter = PlayerCharacterCast;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Encounter Manager couldn't get player character"))
	}
	
	SpawnEnemies(AmountOfEnemiesToSpawn);
	PlayerVelocityOverTime = PlayerCharacter -> GetVelocity();
	CalculatePlayerPositionDrift();
}

float AEncounterManager::CalculatePlayerPositionDrift()
{
	if (PlayerCharacter)
	{
		FVector PlayerPosition = PlayerCharacter -> GetActorLocation();
		PlayerPositionDrift = (PlayerPosition - PlayerPositionBeforeDrift).Length();
		
		if (PlayerPositionDrift >= PlayerPositionDriftThreshold)
		{
			PlayerPositionBeforeDrift = PlayerPosition;
			
			if (OnPlayerPositionDrifted.IsBound())
			{
				OnPlayerPositionDrifted.Broadcast();
			}
		}
	}
	return PlayerPositionDrift;
}



void AEncounterManager::CalculatePlayerVelocity(float DeltaTime)
{
	if (not PlayerCharacter)
		return;
	
	const float PlayerVelocityAlpha = 1.f - FMath::Exp(-DeltaTime / PlayerVelocitySmoothingTime);
	
	const FVector VelocityDelta = (PlayerCharacter->GetVelocity() - PlayerVelocityOverTime ) * PlayerVelocityAlpha;
	PlayerVelocityOverTime = PlayerVelocityOverTime + VelocityDelta;
}




// Called every frame
void AEncounterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CalculatePlayerPositionDrift();
	CalculatePlayerVelocity(DeltaTime);
}


void AEncounterManager::SpawnEnemies(int32 AmountToSpawn)
{
	if (ActiveEnemyClasses.IsEmpty() or AmountToSpawn <= 0)
	{
		return;
	}
	
	
	UNavigationSystemV1* const NavSys = UNavigationSystemV1::GetCurrent( GetWorld() );
	if (not NavSys)
	{
		UE_LOG(LogTemp, Error, TEXT("An NavSys is NULL"));
		return;
	}
	
	FNavLocation DestinationData;
	for (int32 i = 0; i < AmountToSpawn; i++)
	{
		bool const bIsPointValid = NavSys -> GetRandomPointInNavigableRadius(GetActorLocation(), 5000.f, DestinationData);
		if (not bIsPointValid)
		{
			continue;
		}
		
		int32 EnemyClassIndexToSpawn = FMath::RandRange(0, ActiveEnemyClasses.Num() - 1);
		TSubclassOf<AEnemyCharacter> EnemyClassToSpawn = ActiveEnemyClasses[EnemyClassIndexToSpawn];
		if (not EnemyClassToSpawn)
		{
			continue;
		}
		
		// Setting the spawn paramaters for enemy, instead of instantly spawning
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		// Setting where the player should spawn
		const int32 CapsuleHalfHeight = EnemyClassToSpawn.GetDefaultObject() -> GetCapsuleComponent() -> GetScaledCapsuleHalfHeight();
		DestinationData.Location = FVector(DestinationData.Location.X, DestinationData.Location.Y, DestinationData.Location.Z + CapsuleHalfHeight*1.1f);
		
		FTransform EnemyTransform;
		EnemyTransform.SetLocation(DestinationData.Location);
		
		// Setting up the spawning
		AEnemyCharacter* SpawnedEnemy = GetWorld() -> SpawnActorDeferred<AEnemyCharacter>(EnemyClassToSpawn.Get(), EnemyTransform);
		if (not SpawnedEnemy)
		{
			continue;
		}
		
		SpawnedEnemy -> EncounterManager = this;
		
		
		
		// Setting up the height positioning nurture for the enemy
		if (not SpawnedEnemy -> EnemyPositioningNurtureChance.IsEmpty())
		{
			const int32 EnemyPositioningNurtureChance = FMath::RandRange(0, 100);
			
			TArray<EEnemyElevationPositioning> Positionings;
			SpawnedEnemy -> EnemyPositioningNurtureChance.GetKeys(Positionings);
			
			int32 PositionChance = 0;
			for (EEnemyElevationPositioning CurrentPositioning: Positionings)
			{
				PositionChance += SpawnedEnemy -> EnemyPositioningNurtureChance[CurrentPositioning];
				if (PositionChance >= EnemyPositioningNurtureChance)
				{
					SpawnedEnemy -> CurrentPositioning = CurrentPositioning;
					
					int32 IdealElevation = (int32)SpawnedEnemy -> CurrentPositioning - (int32)EEnemyElevationPositioning::EEEP_SameLevel;
					float IdealHeight = -IdealElevation * PositioningHeightThreshold;
					SpawnedEnemy -> IdealHeightDistance = IdealHeight;
					SpawnedEnemy -> PositioningHeightThreshold = PositioningHeightThreshold;
					break;
				}
			}
		}
		
		SpawnedEnemy -> FinishSpawning(EnemyTransform);
		
		TObjectPtr<AEnemyController> EnemyController = Cast<AEnemyController>(SpawnedEnemy -> GetController());
		if (EnemyController)
		{
			EnemyController -> OnPlayerPositionDriftDelegateHandle = OnPlayerPositionDrifted.AddUObject(EnemyController, &AEnemyController::OnPlayerPositionDrift);
		}
		
		Enemies.Add(SpawnedEnemy);
		AmountOfEnemies++;
	}
}


void AEncounterManager::OnEnemyDeath()
{
	if (AmountOfEnemies > 0)
	{
		AmountOfEnemies -= 1;
	}
}

bool AEncounterManager::EnemyRequestAttack(TWeakObjectPtr<AEnemyCharacter> EnemyRequester, int32 AttackCost)
{
	if (CombatManager -> RequestAttack(EnemyRequester, AttackCost))
		return true;
	return false;
}


TObjectPtr<APlayerCharacter> AEncounterManager::GetPlayerCharacter()
{
	return PlayerCharacter;
}

float AEncounterManager::GetPlayerPositionDrift()
{
	return PlayerPositionDrift;
}

float AEncounterManager::GetPlayerPositionDriftThreshold()
{
	return PlayerPositionDriftThreshold;
}

FVector AEncounterManager::GetPlayerVelocityOverTime()
{
	return PlayerVelocityOverTime;
}

TWeakObjectPtr<UCombatManager> AEncounterManager::GetCombatManager()
{
	return CombatManager;
}


