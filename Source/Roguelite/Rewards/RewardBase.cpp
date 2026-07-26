// Fill out your copyright notice in the Description page of Project Settings.


#include "RewardBase.h"

#include "Components/SphereComponent.h"
#include "Roguelite/PC/PlayerCharacter.h"


// Sets default values
ARewardBase::ARewardBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	PickableSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Pickable Sphere"));
	PickableSphere -> SetupAttachment(GetRootComponent());
	PickableSphere -> SetSphereRadius(450.f);
}

// Called when the game starts or when spawned
void ARewardBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARewardBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void ARewardBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		PlayerCharacter -> NewInteractable(this);
	}
}



void ARewardBase::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		PlayerCharacter -> RemoveInteractable(this);
	}
}


void ARewardBase::Interact(APlayerCharacter* PlayerInteractor)
{
	Destroy();
}



