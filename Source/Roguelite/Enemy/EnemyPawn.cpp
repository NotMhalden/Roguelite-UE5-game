// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

#include "Components/StaticMeshComponent.h"


// Sets default values
AEnemyPawn::AEnemyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	CapsuleComponent -> InitCapsuleSize(34.0f, 88.0f);
	CapsuleComponent -> SetupAttachment(GetRootComponent());
	CapsuleComponent -> SetCanEverAffectNavigation(false);
	RootComponent = CapsuleComponent;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh -> SetCanEverAffectNavigation(false);
	Mesh -> SetupAttachment(CapsuleComponent);
}


// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}




void AEnemyPawn::TakeDamage(int DamageTaken)
{
	Health -= DamageTaken;
	if (Health <= 0)
	{
		Death();
	}
}


void AEnemyPawn::Death()
{
	Destroy();
}

