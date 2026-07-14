// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class AEnemyCharacter;



DECLARE_DELEGATE(FOnEnemyTokenChange)

DECLARE_MULTICAST_DELEGATE(FOnEnemyDeathDelegate)
inline FOnEnemyDeathDelegate OnEnemyDeathDelegate;

DECLARE_MULTICAST_DELEGATE_OneParam(FRemoveEnemyAttacker, TWeakObjectPtr<AEnemyCharacter> /* EnemyAttacker */)
inline FRemoveEnemyAttacker RemoveEnemyAttacker;

DECLARE_MULTICAST_DELEGATE(FOnPlayerPositionDrifted)
inline FOnPlayerPositionDrifted OnPlayerPositionDrifted; 