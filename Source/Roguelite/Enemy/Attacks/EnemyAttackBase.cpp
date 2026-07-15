// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttackBase.h"

UEnemyAttackBase::UEnemyAttackBase()
{
	
}


bool UEnemyAttackBase::Begin(AEnemyCharacter* Self, AActor* TargetActor)
{
	return true;
}


bool UEnemyAttackBase::Tick(AEnemyCharacter* Self, AActor* TargetActor, float DeltaTime)
{
	return true;
}


int32 UEnemyAttackBase::Score(AEnemyCharacter* Self, AActor* TargetActor)
{
	return 0;
}

int32 UEnemyAttackBase::GetTokenCost()
{
	return TokenCost;
}
