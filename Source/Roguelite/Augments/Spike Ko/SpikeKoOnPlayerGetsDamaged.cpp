// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeKoOnPlayerGetsDamaged.h"

#include "Roguelite/Enemy/EnemyCharacter.h"

void USpikeKoOnPlayerGetsDamaged::OnPlayerGetsDamaged(APlayerCharacter* PlayerCharacter, AEnemyCharacter* EnemyAttacker, int32& DamageTaken)
{
	if (not EnemyAttacker)
		return;
	
	if (FMath::FRandRange(0.f,100.f) < DamageAttackerChance)
	{
		EnemyAttacker -> TakeDamage(DamageDealtToAttacker);
	}
}
