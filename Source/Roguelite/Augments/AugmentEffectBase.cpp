// Fill out your copyright notice in the Description page of Project Settings.


#include "AugmentEffectBase.h"
#include "AugmentDataAsset.h"

void UAugmentEffectBase::OnPlayerGetsDamaged(APlayerCharacter* PlayerCharacter, AEnemyCharacter* EnemyAttacker,
                                             int32& DamageTaken)
{
}

void UAugmentEffectBase::OnMainActionFireHit(APlayerCharacter* PlayerCharacter, int32& Damage)
{
}

void UAugmentEffectBase::OnSecondaryActionFireHit(APlayerCharacter* PlayerCharacter, int32& Damage)
{
}

void UAugmentEffectBase::OnEffectLevelUp(int32 LevelIncreased)
{
}

void UAugmentEffectBase::OnEffectRarityImproved(EAugmentRarity RarityImproved)
{
}
