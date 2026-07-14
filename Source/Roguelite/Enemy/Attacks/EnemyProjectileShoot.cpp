// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectileShoot.h"

#include "Engine/World.h"
#include "TimerManager.h"
#include "Roguelite/Enemy/EnemyCharacter.h"
#include "Roguelite/Weapon/Bullet/BulletBase.h"

UEnemyProjectileShoot::UEnemyProjectileShoot()
{
	TokenCost = 1;
}

bool UEnemyProjectileShoot::Begin(AEnemyCharacter* Self, AActor* TargetActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile Shoot"))
	CurrentShots = 0;
	return true;
}

bool UEnemyProjectileShoot::Tick(AEnemyCharacter* Self, AActor* TargetActor, float DeltaTime)
{
	if (CurrentShots >= AmountOfShots)
		return true;
	
	if (bWeaponCooling)
		return false;
	if (not BulletClass)
		return false;
	
	UWorld* const World = GetWorld();
	if (not World)
		return false;
	
	bWeaponCooling = true;
	
	const FVector SpawnLocation = Self -> GetActorLocation() + Self -> GetActorForwardVector() * 70.0;
	const FVector TargetLocation = TargetActor->GetActorLocation() + TargetActor->GetVelocity() * 100.0;
	const FVector Direction = (TargetLocation - SpawnLocation).GetSafeNormal();
	
	
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	UE_LOG(LogTemp, Warning, TEXT("Enemy shot"));
	auto* Bullet = World -> SpawnActor<ABulletBase>(BulletClass, SpawnLocation, Direction.Rotation(), ActorSpawnParams);
	Bullet -> BulletDamage *= Damage;

	
	FireRateCooldown = 1 / FireRate;
	World -> GetTimerManager().SetTimer(FireRateTimerHandle, this, &UEnemyProjectileShoot::FireRateDelayOver, FireRateCooldown, false);
	
	CurrentShots++;
	return false;
}

int32 UEnemyProjectileShoot::Score(AEnemyCharacter* Self, AActor* TargetActor)
{
	return 0;
}

void UEnemyProjectileShoot::FireRateDelayOver()
{
	bWeaponCooling = false;
}
