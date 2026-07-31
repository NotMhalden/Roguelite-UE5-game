// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomMover.h"
#include "Components/BoxComponent.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Roguelite/PC/PlayerCharacter.h"
#include "Roguelite/PC/PlayerDelegates.h"
#include "Roguelite/Run/RunStateSubsystem.h"


// Sets default values
ARoomMover::ARoomMover()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
		
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	TriggerBox -> SetupAttachment(GetRootComponent());
	TriggerBox -> SetBoxExtent(FVector(400.f, 300.f, 400.f));
}

// Called when the game starts or when spawned
void ARoomMover::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ARoomMover::Interact(APlayerCharacter* PlayerInteractor)
{
	if (bDoorIsOpen)
	{
		UE_LOG(LogTemp, Warning, TEXT("Interacting with %s"), *GetName());
		
		URunStateSubsystem* RunState = GetGameInstance()->GetSubsystem<URunStateSubsystem>();
		RunState -> PlayerClearedRoom();
		
		if (SaveRunStatePlayerVariablesDelegate.IsBound())
			SaveRunStatePlayerVariablesDelegate.Broadcast(PlayerInteractor);
		
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelToLoad);
	}
}


void ARoomMover::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		PlayerCharacter -> NewInteractable(this);
	}
}

void ARoomMover::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		PlayerCharacter -> RemoveInteractable(this);
	}
}
