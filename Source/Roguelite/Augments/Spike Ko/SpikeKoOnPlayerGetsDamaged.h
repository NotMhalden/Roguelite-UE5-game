// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Roguelite/Augments/AugmentEffectBase.h"
#include "SpikeKoOnPlayerGetsDamaged.generated.h"


/**
 * 
 */
UCLASS()
class ROGUELITE_API USpikeKoOnPlayerGetsDamaged : public UAugmentEffectBase
{
	GENERATED_BODY()

public:
	virtual void OnPlayerGetsDamaged(APlayerCharacter* PlayerCharacter, AEnemyCharacter* EnemyAttacker, int32& DamageTaken) override;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Augments|Stats", meta=(ClampMin=0.f, ClampMax=100.f))
	float DamageAttackerChance = 10.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Augments|Stats", meta=(ClampMin=0.f))
	int32 DamageDealtToAttacker = 35;
};
