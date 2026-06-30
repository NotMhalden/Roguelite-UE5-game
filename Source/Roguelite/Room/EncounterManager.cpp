// Fill out your copyright notice in the Description page of Project Settings.


#include "EncounterManager.h"

#include "NavigationSystem.h"
#include "Components/CapsuleComponent.h"
#include "Roguelite/Enemy/EnemyCharacter.h"
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
}

// Called every frame
void AEncounterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
		
		
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		const int32 CapsuleHalfHeight = EnemyClassToSpawn.GetDefaultObject() -> GetCapsuleComponent() -> GetScaledCapsuleHalfHeight();
		DestinationData.Location = FVector(DestinationData.Location.X, DestinationData.Location.Y, DestinationData.Location.Z + CapsuleHalfHeight);
		
		AActor* SpawnedActor = GetWorld() -> SpawnActor(EnemyClassToSpawn.Get(), &DestinationData.Location);
		AEnemyCharacter* SpawnedEnemy = Cast<AEnemyCharacter>(SpawnedActor);
		if (not SpawnedEnemy)
		{
			continue;
		}
		
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
					break;
				}
			}
		}
		
		
		SpawnedEnemy -> EncounterManager = this;
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



TObjectPtr<APlayerCharacter> AEncounterManager::GetPlayerCharacter()
{
	return PlayerCharacter;
}

