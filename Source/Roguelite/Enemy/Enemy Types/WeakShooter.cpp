// Fill out your copyright notice in the Description page of Project Settings.


#include "WeakShooter.h"

#include "Components/CapsuleComponent.h"


// Sets default values
AWeakShooter::AWeakShooter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MaxSpeed = 800.0f;
	MaxHealth = 75.0f;
	Health = MaxHealth;
	IdealDistance = 1700.f;
	
	GetCapsuleComponent() -> SetCapsuleRadius(45.f);
	GetCapsuleComponent() -> SetCapsuleHalfHeight(90.f);
}

// Called when the game starts or when spawned
void AWeakShooter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeakShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWeakShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

