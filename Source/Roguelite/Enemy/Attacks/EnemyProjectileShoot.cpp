// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectileShoot.h"

UEnemyProjectileShoot::UEnemyProjectileShoot()
{
	TokenCost = 1;
}

bool UEnemyProjectileShoot::Begin(AEnemyCharacter* Self, AActor* TargetActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile Shoot"))
	return true;
}

bool UEnemyProjectileShoot::Tick(AEnemyCharacter* Self, AActor* TargetActor, float DeltaTime)
{
	return false;
}

int32 UEnemyProjectileShoot::Score(AEnemyCharacter* Self, AActor* TargetActor)
{
	return 0;
}

