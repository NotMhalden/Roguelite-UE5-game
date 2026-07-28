// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AugmentEffectBase.generated.h"

enum class EAugmentRarity : uint8;
class APlayerCharacter;
class AEnemyCharacter;


/**
 * 
 */
UCLASS(Abstract, EditInlineNew)
class ROGUELITE_API UAugmentEffectBase : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void OnPlayerGetsDamaged(APlayerCharacter* PlayerCharacter, AEnemyCharacter* EnemyAttacker, int32& DamageTaken);
	virtual void OnMainActionFireHit(APlayerCharacter* PlayerCharacter, int32& Damage);
	virtual void OnSecondaryActionFireHit(APlayerCharacter* PlayerCharacter, int32& Damage);
	
	virtual void OnEffectLevelUp(int32 LevelIncreased);
	virtual void OnEffectRarityImproved(EAugmentRarity RarityImproved);
};
