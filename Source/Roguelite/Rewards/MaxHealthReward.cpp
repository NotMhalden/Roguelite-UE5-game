// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxHealthReward.h"

#include "Roguelite/PC/PlayerCharacter.h"


// Sets default values
AMaxHealthReward::AMaxHealthReward()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMaxHealthReward::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMaxHealthReward::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMaxHealthReward::Interact(APlayerCharacter* PlayerInteractor)
{
	PlayerInteractor -> SetMaxHealth( PlayerInteractor->GetMaxHealth() + MaxHealthToGive );
	PlayerInteractor -> SetHealth( PlayerInteractor->GetHealth() + MaxHealthToGive );
	
	Super::Interact(PlayerInteractor);
}

