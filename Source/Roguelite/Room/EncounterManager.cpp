// Fill out your copyright notice in the Description page of Project Settings.


#include "EncounterManager.h"

#include "NavigationSystem.h"
#include "Roguelite/Enemy/EnemyPawn.h"


// Sets default values
AEncounterManager::AEncounterManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEncounterManager::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnEnemies(AmountOfEnemiesToSpawn);
}

// Called every frame
void AEncounterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AEncounterManager::SpawnEnemies(int32 AmountToSpawn)
{
	if (ActiveEnemyClasses.IsEmpty())
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
		bool const bIsPointValid = NavSys -> GetRandomPoint(DestinationData);
		if (not bIsPointValid)
		{
			continue;
		}
		
		int32 EnemyClassIndexToSpawn = FMath::RandRange(0, ActiveEnemyClasses.Num() - 1);
		TSubclassOf<AEnemyPawn> EnemyClassToSpawn = ActiveEnemyClasses[EnemyClassIndexToSpawn];
		GetWorld() -> SpawnActor(EnemyClassToSpawn.Get(), &DestinationData.Location);
		
	}

	
	
}


void AEncounterManager::OnEnemyDeath()
{
}

