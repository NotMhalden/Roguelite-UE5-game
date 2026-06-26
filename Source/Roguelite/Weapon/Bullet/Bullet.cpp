// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Roguelite/Enemy/EnemyPawn.h"


// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent -> InitSphereRadius(5.0f);
	SphereComponent -> SetupAttachment(GetRootComponent());
	SphereComponent -> BodyInstance.SetCollisionProfileName("Projectile");
	SphereComponent -> OnComponentHit.AddDynamic(this, &ABullet::OnCollision);
	RootComponent = SphereComponent;
	
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh -> SetupAttachment(SphereComponent);
	Mesh -> BodyInstance.SetCollisionProfileName("Projectile");
	
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	MovementComponent -> UpdatedComponent = SphereComponent;
	MovementComponent -> InitialSpeed = BulletSpeed;
	MovementComponent -> MaxSpeed = BulletSpeed;
	MovementComponent -> ProjectileGravityScale = 0.f;
	
	InitialLifeSpan = BulletLifespan;
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
	if (auto* EnemyPlayer = Cast<AEnemyPawn>(OtherActor))
	{
		EnemyPlayer -> TakeDamage(BulletDamage);
	}
	Destroy();
}

