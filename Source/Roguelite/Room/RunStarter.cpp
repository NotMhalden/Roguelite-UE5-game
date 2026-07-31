// Fill out your copyright notice in the Description page of Project Settings.


#include "RunStarter.h"

#include "Components/BoxComponent.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Roguelite/PC/PlayerCharacter.h"
#include "Roguelite/Run/RunStateSubsystem.h"


// Sets default values
ARunStarter::ARunStarter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARunStarter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARunStarter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARunStarter::Interact(APlayerCharacter* PlayerInteractor)
{
	UE_LOG(LogTemp, Warning, TEXT("Interacting with %s"), *GetName());
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelToLoad);
}