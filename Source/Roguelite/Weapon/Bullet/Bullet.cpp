// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Roguelite/Enemy/EnemyCharacter.h"


// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BulletDamage = 15.f;
	BulletLifespan = 5.f;
	BulletSpeed = 5500.f;
	
	MovementComponent -> InitialSpeed = BulletSpeed;
	MovementComponent -> MaxSpeed = BulletSpeed;
	MovementComponent -> ProjectileGravityScale = 0.f;
	InitialLifeSpan = BulletLifespan;
	
	SphereComponent -> SetSphereRadius(45.f);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet::OnCollision(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (auto* EnemyPlayer = Cast<AEnemyCharacter>(OtherActor))
	{
		EnemyPlayer -> TakeDamage(BulletDamage);
	}
	Destroy();
}
