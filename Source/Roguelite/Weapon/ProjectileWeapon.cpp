// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeapon.h"

#include "TimerManager.h"
#include "Bullet/Bullet.h"
#include "Engine/World.h"


// Sets default values
AProjectileWeapon::AProjectileWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Damage = 25;
	AttackRate = 5.f;
}

// Called when the game starts or when spawned
void AProjectileWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileWeapon::MainAttack(FVector CameraForwardVector, FVector CameraLocation)
{
	if (bWeaponCooling)
	{
		return;
	}
	
	if (not BulletClass)
	{
		return;
	}
	
	UWorld* const World = GetWorld();
	if (not World)
	{
		return;
	}
	
	bWeaponCooling = true;
	FRotator SpawnRotation = CameraForwardVector.Rotation();
	FVector SpawnLocation = CameraLocation + CameraForwardVector * 70.0;
	
	
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	UE_LOG(LogTemp, Warning, TEXT("Bullet Spawned"));
	auto* Bullet = World -> SpawnActor<ABullet>(BulletClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	Bullet -> BulletDamage = Damage;
	
	AttackRateCooldown = 1 / AttackRate;
	GetWorldTimerManager().SetTimer(AttackRateTimerHandle, this, &AHitscanWeapon::FireRateDelayOver, AttackRateCooldown, false);
}

