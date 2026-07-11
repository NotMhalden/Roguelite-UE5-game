// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanWeapon.h"

#include "TimerManager.h"
#include "Bullet/Bullet.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "Roguelite/Enemy/EnemyCharacter.h"


// Sets default values
AHitscanWeapon::AHitscanWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh -> SetupAttachment(GetRootComponent());

	
	
	TraceChannel = ECC_Visibility;
	
	
	Damage = 10;
	AttackRate = 10.f;
}

// Called when the game starts or when spawned
void AHitscanWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHitscanWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHitscanWeapon::MainAction(FVector CameraForwardVector, FVector CameraLocation)
{
	//UE_LOG(LogTemp, Warning, TEXT("Main Action done"))
	if (bWeaponCooling)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Weapon cooling"))
		return;
	}
		
	const UWorld* World = GetWorld();
	if (not World)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Cant get world"))
		return;
	}
	
	
	// Trace origin / direction
	const FVector TraceStart = CameraLocation;
	const FVector Direction = CameraForwardVector;
	const FVector TraceEnd = TraceStart + Direction * 6000.f;
	
	const FVector FakeBulletTraceStart = Mesh -> GetComponentLocation();
	const FVector FakeBulletTraceEnd = FakeBulletTraceStart + Direction * 70.f;
	
	// Prepare collision params
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = false;
	QueryParams.bReturnPhysicalMaterial = false;
	
	// Perform trace
	FHitResult Hit;
	const bool bDidHit = World -> LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannel, QueryParams);
	// UE_LOG(LogTemp, Warning, TEXT("Hitscan shot"))
	
	DrawDebugLine(World, FakeBulletTraceStart, FakeBulletTraceEnd, FColor::Orange, false, 0.01f, 0, 1.5f);
	
	
	// No hit
	if (not bDidHit)
	{
		// DrawDebugLine(World, TraceStart, TraceEnd, FColor::Red, false, 1.0f, 0, 0.5f);
		return;
	}
	
	// We hit something.
	DrawDebugSphere(World, Hit.ImpactPoint, 12.0f, 8, FColor::Blue, false, 1.0f);
	
	
	
	AActor* HitActor = Hit.GetActor();
	if (not HitActor)
	{
		// Hit something without an actor, in our case it will be probably nothing
		DrawDebugLine(World, TraceStart, TraceEnd, FColor::Green, false, 1.0f, 0, 0.5f);
		return;
	}
	
	if (AEnemyCharacter* HitPawn = Cast<AEnemyCharacter>(HitActor))
	{
		int32 CalculatedDamage = Damage;
		HitPawn -> TakeDamage(CalculatedDamage);
	}
	
	// Weapon reload system
	bWeaponCooling = true;
	AttackRateCooldown = 1 / AttackRate;
	GetWorldTimerManager().SetTimer(AttackRateTimerHandle, this, &AHitscanWeapon::FireRateDelayOver, AttackRateCooldown, false);

}

void AHitscanWeapon::FireRateDelayOver()
{
	bWeaponCooling = false;
}

