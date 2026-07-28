// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Roguelite/PC/PlayerCharacter.h"


// Sets default values
AEnemyProjectile::AEnemyProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BulletSpeed = 3000.f;
	BulletDamage = 1.f;
	
	MovementComponent -> InitialSpeed = BulletSpeed;
	MovementComponent -> MaxSpeed = BulletSpeed;
	MovementComponent -> ProjectileGravityScale = 0.f;
	
	/*
	MovementComponent -> bIsHomingProjectile = true;
	MovementComponent -> HomingAccelerationMagnitude = 0.5f;
	*/
	
	Mesh -> SetRelativeScale3D(FVector(0.1f,0.1f,0.1f));
	Mesh -> SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
	
	SphereComponent -> SetSphereRadius(25.f);
	SphereComponent -> SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
	
}

// Called when the game starts or when spawned
void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyProjectile::OnCollision(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (auto* Player = Cast<APlayerCharacter>(OtherActor))
	{
		Player -> TakeDamage(BulletDamage, EnemyAttacker);
	}
	Destroy();
}

