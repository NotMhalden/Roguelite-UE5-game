// Fill out your copyright notice in the Description page of Project Settings.


#include "WalkingEnemy.h"
#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
AWalkingEnemy::AWalkingEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));
	MovementComponent -> MaxSpeed = MaxSpeed;
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AWalkingEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWalkingEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWalkingEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}


