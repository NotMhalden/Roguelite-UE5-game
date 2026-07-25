// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectileShoot.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Projectiles/EnemyProjectile.h"
#include "Roguelite/Enemy/EnemyCharacter.h"
#include "Roguelite/PC/PlayerCharacter.h"
#include "Roguelite/Room/EncounterManager.h"

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
	{
		Reset();
		return true;
	}
	
	if (bWeaponCooling)
		return false;
	if (not BulletClass)
		return false;
	
	if (not HasLOS(Self, Self->GetActorLocation(),TargetActor->GetActorLocation()))
	{
		Reset();
		return true;
	}
	
	UWorld* const World = GetWorld();
	if (not World)
		return false;
	
	if (not Self->EncounterManager.Get())
	{
		Reset();
		return true;
	}
	
	bWeaponCooling = true;
	
	const FVector SpawnLocation = Self -> GetActorLocation() + Self -> GetActorForwardVector() * 70.0;
	
	const float DistanceToPlayer = (TargetActor->GetActorLocation() - SpawnLocation).Size();
	const float PredictionWeight = DistanceToPlayer / BulletClass.GetDefaultObject()->BulletSpeed;
	
	const float Accuracy = FMath::FRandRange(MinAccuracy, MaxAccuracy);
	const FVector TargetLocation = TargetActor->GetActorLocation() + Self->EncounterManager->GetPlayerVelocityOverTime() * PredictionWeight * Accuracy;
	
	const FVector Direction = (TargetLocation - SpawnLocation).GetSafeNormal();
	
	
	if (IsPathBlocked(Self, TargetActor, SpawnLocation, TargetLocation))
	{
		Reset();
		return true;
	}
	
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
	
	if (not HasLOS(Self, Self->GetActorLocation(), TargetActor->GetActorLocation()))
		return 0;
	
	return TokenCost;
}



void UEnemyProjectileShoot::FireRateDelayOver()
{
	bWeaponCooling = false;
}




bool UEnemyProjectileShoot::HasLOS(AEnemyCharacter* Self, FVector StartLocation, FVector TargetLocation)
{
	UWorld* World = GetWorld();
	if (not World)
		return false;
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Self);
	ECollisionChannel TraceChannel = ECC_Camera;
	
	FHitResult Hit;
	const bool bDidHit = World -> LineTraceSingleByChannel(Hit, StartLocation, TargetLocation, TraceChannel, QueryParams);
	
	if (not bDidHit)
		return false;
	
	APlayerCharacter* PC = Cast<APlayerCharacter>(Hit.GetActor());
	if (not PC)
		return false;
	
	return true;
}

bool UEnemyProjectileShoot::IsPathBlocked(AEnemyCharacter* Self, AActor* TargetToIgnore, FVector StartLocation, FVector TargetLocation)
{
	UWorld* World = GetWorld();
	if (not World)
		return true;
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Self);
	QueryParams.AddIgnoredActor(TargetToIgnore);
	
	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	
	FHitResult Hit;
	const bool bDidHit = World -> LineTraceSingleByObjectType(Hit, StartLocation, TargetLocation, ObjectParams, QueryParams);
	
	if (bDidHit)
		return true;
	
	return false;
}

void UEnemyProjectileShoot::Reset()
{
	bWeaponCooling = false;
}
