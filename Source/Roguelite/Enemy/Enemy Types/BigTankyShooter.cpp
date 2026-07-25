// Fill out your copyright notice in the Description page of Project Settings.


#include "BigTankyShooter.h"

#include "Components/CapsuleComponent.h"


// Sets default values
ABigTankyShooter::ABigTankyShooter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MaxSpeed = 300.0f;
	MaxHealth = 175.0f;
	Health = MaxHealth;
	IdealDistance = 1300.f;
	
	GetCapsuleComponent() -> SetCapsuleRadius(60.f);
	GetCapsuleComponent() -> SetCapsuleHalfHeight(140.f);
}

// Called when the game starts or when spawned
void ABigTankyShooter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABigTankyShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABigTankyShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

