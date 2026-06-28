// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EncounterManager.generated.h"

class AEnemyPawn;
class APlayerCharacter;

UCLASS()
class ROGUELITE_API AEncounterManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEncounterManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SpawnEnemies(int32 AmountToSpawn);
	
	void OnEnemyDeath();
	
	
	
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<APlayerCharacter> PlayerCharacter = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<AEnemyPawn*> Enemies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin = 0))
	int32 AmountOfEnemies = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AEnemyPawn>> ActiveEnemyClasses;
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin = 0))
	int32 CurrentWave = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin = 0))
	int32 TotalWaves = 3;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin = 0))
	int32 Difficulty = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin = 0))
	int32 AmountOfEnemiesToSpawn = 5;
};
