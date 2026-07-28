// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EncounterManager.generated.h"

class ARewardBase;
class UCombatManager;
class AEnemyCharacter;
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

	float CalculatePlayerPositionDrift();
	
	void CalculatePlayerVelocity(float DeltaTime);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SpawnEnemies(int32 AmountToSpawn);
	
	void OnEnemyDeath();
	
	bool EnemyRequestAttack(TWeakObjectPtr<AEnemyCharacter> EnemyRequester, int32 AttackCost);
	
	TObjectPtr<APlayerCharacter> GetPlayerCharacter();
	float GetPlayerPositionDrift();
	float GetPlayerPositionDriftThreshold();
	
	FVector GetPlayerVelocityOverTime();
	
	TWeakObjectPtr<UCombatManager> GetCombatManager();
	
	
	
public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Encounter|AI", meta = (AllowPrivateAccess = "true"))
	TArray<AEnemyCharacter*> Enemies;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Encounter|AI", meta = (AllowPrivateAccess = "true", ClampMin = 0))
	int32 AmountOfEnemies = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Encounter", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AEnemyCharacter>> ActiveEnemyClasses;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Encounter", meta = (AllowPrivateAccess = "true", ClampMin = 0))
	int32 CurrentWave = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Encounter", meta = (AllowPrivateAccess = "true", ClampMin = 0))
	int32 TotalWaves = 3;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Encounter", meta = (AllowPrivateAccess = "true", ClampMin = 0))
	int32 Difficulty = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Encounter", meta = (AllowPrivateAccess = "true", ClampMin = 0))
	int32 AmountOfEnemiesToSpawn = 5;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Encounter|AI", meta = (AllowPrivateAccess = "true", ClampMin = 0.f))
	float PositioningHeightThreshold = 150.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Encounter|AI", meta = (AllowPrivateAccess = "true", ClampMin = 0.f))
	float PositioningHeightPlateau = PositioningHeightThreshold/2;

	
protected:
	UPROPERTY(VisibleAnywhere, Category="Encounter|Player")
	TObjectPtr<APlayerCharacter> PlayerCharacter = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category="Encounter|Player")
	float PlayerPositionDriftThreshold = 500.f;
	UPROPERTY(VisibleAnywhere, Category="Encounter|Player")
	float PlayerPositionDrift = 0.f;
	FVector PlayerPositionBeforeDrift;
	
	UPROPERTY(VisibleAnywhere, Category="Encounter|Player")
	FVector PlayerVelocityOverTime;
	UPROPERTY(EditDefaultsOnly, Category="Encounter|Player", meta=(ClampMin = 0.f))
	float PlayerVelocitySmoothingTime = 0.3f;
	
	
protected:
	UPROPERTY(EditAnywhere, Category="Encounter", meta = (AllowPrivateAccess = "true", ClampMin = 0))
	TArray<TSubclassOf<ARewardBase>> ActiveRewardClasses;
	
	
	
protected:
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category="Encounter|Data", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCombatManager> CombatManager;

};
