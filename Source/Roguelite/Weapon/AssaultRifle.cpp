// Fill out your copyright notice in the Description page of Project Settings.


#include "AssaultRifle.h"

#include "Bullet/Bullet.h"


// Sets default values
AAssaultRifle::AAssaultRifle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Damage = 25;
	AttackRate = 5.f;
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
	Super::MainAction(CameraForwardVector, CameraLocation);
}

