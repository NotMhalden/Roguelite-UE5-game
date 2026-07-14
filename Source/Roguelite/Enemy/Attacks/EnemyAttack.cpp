// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttack.h"

UEnemyAttack::UEnemyAttack()
{
	
}


bool UEnemyAttack::Begin(AEnemyCharacter* Self, AActor* TargetActor)
{
	return true;
}


bool UEnemyAttack::Tick(AEnemyCharacter* Self, AActor* TargetActor, float DeltaTime)
{
	return true;
}


int32 UEnemyAttack::Score(AEnemyCharacter* Self, AActor* TargetActor)
{
	return 0;
}

int32 UEnemyAttack::GetTokenCost()
{
	return TokenCost;
}
