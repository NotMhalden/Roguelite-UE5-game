// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EncounterManager.generated.h"

class AEnemyCharacter;
class APlayerCharacter;


DECLARE_MULTICAST_DELEGATE(FPlayerPositionDriftedDelegate)
inline FPlayerPositionDriftedDelegate PlayerPositionDriftedDelegate; 


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

	float CalculatePlayerPositionDrift();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SpawnEnemies(int32 AmountToSpawn);
	
	void OnEnemyDeath();
	
	TObjectPtr<APlayerCharacter> GetPlayerCharacter();
	float GetPlayerPositionDrift();
	float GetPlayerPositionDriftThreshold();
	
	
public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<AEnemyCharacter*> Enemies;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin = 0))
	int32 AmountOfEnemies = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AEnemyCharacter>> ActiveEnemyClasses;
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin = 0))
	int32 CurrentWave = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin = 0))
	int32 TotalWaves = 3;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin = 0))
	int32 Difficulty = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin = 0))
	int32 AmountOfEnemiesToSpawn = 5;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin = 0.f))
	float PositioningHeightThreshold = 150.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ClampMin = 0.f))
	float PositioningHeightPlateau = PositioningHeightThreshold/2;
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<APlayerCharacter> PlayerCharacter = nullptr;
	UPROPERTY(EditDefaultsOnly)
	float PlayerPositionDriftThreshold = 500.f;
	UPROPERTY(VisibleAnywhere)
	float PlayerPositionDrift = 0.f;
	FVector PlayerPositionBeforeDrift;
};
