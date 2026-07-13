// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAttack.h"
#include "EnemyProjectileShoot.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew, DisplayName = "Projectile Shoot")
class ROGUELITE_API UEnemyProjectileShoot : public UEnemyAttack
{
	GENERATED_BODY()

public:
	UEnemyProjectileShoot();
	virtual bool Begin(AEnemyCharacter* Self, AActor* TargetActor) override;
	virtual bool Tick(AEnemyCharacter* Self, AActor* TargetActor, float DeltaTime) override;
	virtual int32 Score(AEnemyCharacter* Self, AActor* TargetActor) override;
};
