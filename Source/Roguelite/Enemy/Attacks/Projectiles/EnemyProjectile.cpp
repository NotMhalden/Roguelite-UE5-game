// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Roguelite/PC/PlayerCharacter.h"


// Sets default values
AEnemyProjectile::AEnemyProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BulletSpeed = 5500.f;
	
	MovementComponent -> InitialSpeed = BulletSpeed;
	MovementComponent -> MaxSpeed = BulletSpeed;
	MovementComponent -> ProjectileGravityScale = 0.f;
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
		Player -> TakeDamage(BulletDamage);
	}
	Destroy();
}

