// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletBase.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ABulletBase::ABulletBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent -> InitSphereRadius(5.0f);
	SphereComponent -> SetupAttachment(GetRootComponent());
	SphereComponent -> BodyInstance.SetCollisionProfileName("Projectile");
	SphereComponent -> OnComponentHit.AddDynamic(this, &ABulletBase::OnCollision);
	RootComponent = SphereComponent;
	
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh -> SetupAttachment(SphereComponent);
	Mesh -> BodyInstance.SetCollisionProfileName("Projectile");
	
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	MovementComponent -> UpdatedComponent = SphereComponent;
}

// Called when the game starts or when spawned
void ABulletBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABulletBase::OnCollision(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
}