// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAttackBase.h"
#include "EnemyProjectileShoot.generated.h"

class AEnemyProjectile;
/**
 * 
 */
UCLASS(EditInlineNew, DisplayName = "Projectile Shoot")
class ROGUELITE_API UEnemyProjectileShoot : public UEnemyAttackBase
{
	GENERATED_BODY()

public:
	UEnemyProjectileShoot();
	virtual bool Begin(AEnemyCharacter* Self, AActor* TargetActor) override;
	virtual bool Tick(AEnemyCharacter* Self, AActor* TargetActor, float DeltaTime) override;
	virtual int32 Score(AEnemyCharacter* Self, AActor* TargetActor) override;
	
protected:
	void FireRateDelayOver();
	
private:
	bool HasLOS(AEnemyCharacter* Self, FVector StartLocation, FVector TargetLocation);
	bool IsPathBlocked(AEnemyCharacter* Self, AActor* TargetToIgnore, FVector StartLocation, FVector TargetLocation);
	
	void Reset();
	
	
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AttackData", meta = (AllowPrivateAccess = "true", ClampMax = "15.0"))
	int32 Damage = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AttackData", meta = (AllowPrivateAccess = "true", ClampMax = "15.0"))
	float FireRate = 2;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AttackData", meta = (AllowPrivateAccess = "true", ClampMin = "0.0", ClampMax = "1.0"))
	float MinAccuracy = 0.6f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AttackData", meta = (AllowPrivateAccess = "true", ClampMin = "0.0", ClampMax = "1.0"))
	float MaxAccuracy = 0.9f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AttackData", meta = (AllowPrivateAccess = "true", ClampMax = "15.0"))
	int32 AmountOfShots = 5;
	int32 CurrentShots = 0;
	
protected:
	FTimerHandle FireRateTimerHandle;
	bool bWeaponCooling = false;
	float FireRateCooldown = 0.1f;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AttackData", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEnemyProjectile> BulletClass = nullptr;
};
