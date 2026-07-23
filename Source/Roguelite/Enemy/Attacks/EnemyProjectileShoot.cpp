// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectileShoot.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Roguelite/Enemy/EnemyCharacter.h"
#include "Roguelite/PC/PlayerCharacter.h"
#include "Roguelite/Room/EncounterManager.h"
#include "Roguelite/Weapon/Bullet/BulletBase.h"

UEnemyProjectileShoot::UEnemyProjectileShoot()
{
	TokenCost = 2;
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
	
	if (not LOSCheck(Self, TargetActor->GetActorLocation()))
		return true;
	
	UWorld* const World = GetWorld();
	if (not World)
		return false;
	
	bWeaponCooling = true;
	
	const FVector SpawnLocation = Self -> GetActorLocation() + Self -> GetActorForwardVector() * 70.0;
	
	const float DistanceToPlayer = (TargetActor->GetActorLocation() - SpawnLocation).Size();
	const float PredictionWeight = DistanceToPlayer / BulletClass.GetDefaultObject()->BulletSpeed;
	const FVector TargetLocation = TargetActor->GetActorLocation() + Self->EncounterManager->GetPlayerVelocityOverTime() * PredictionWeight;
	
	const FVector Direction = (TargetLocation - SpawnLocation).GetSafeNormal();
	
	if (not LOSCheck(Self, TargetActor->GetActorLocation(), false))
		return true;
	
	DrawDebugSphere(World, TargetLocation, 50.f, 12, FColor::Cyan, false, PredictionWeight);
	
	
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
	if (not Self)
		return 0;
	if (not TargetActor)
		return 0;
	
	if (not LOSCheck(Self, TargetActor->GetActorLocation()))
		return 0;
	
	return TokenCost;
}



void UEnemyProjectileShoot::FireRateDelayOver()
{
	bWeaponCooling = false;
}




bool UEnemyProjectileShoot::LOSCheck(AEnemyCharacter* Self, FVector TargetLocation, bool bShouldHitPlayer)
{
	UWorld* World = GetWorld();
	if (not World)
		return false;
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Self);
	ECollisionChannel TraceChannel = ECC_Camera;
	
	FHitResult Hit;
	const bool bDidHit = World -> LineTraceSingleByChannel(Hit, Self->GetActorLocation(), TargetLocation, TraceChannel, QueryParams);
	
	if (not bDidHit)
		return false;
	
	if (bShouldHitPlayer)
	{
		APlayerCharacter* PC = Cast<APlayerCharacter>(Hit.GetActor());
		if (not PC)
			return false;
	}
	
	return true;
}