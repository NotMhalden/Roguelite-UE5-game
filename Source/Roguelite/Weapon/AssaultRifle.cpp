// Fill out your copyright notice in the Description page of Project Settings.


#include "AssaultRifle.h"

#include "Bullet/Bullet.h"


// Sets default values
AAssaultRifle::AAssaultRifle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAssaultRifle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAssaultRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAssaultRifle::MainAction(FVector CameraForwardVector, FVector CameraLocation)
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
	GetWorldTimerManager().SetTimer(AttackRateTimerHandle, this, &AWeapon::FireRateDelayOver, AttackRateCooldown, false);
}

