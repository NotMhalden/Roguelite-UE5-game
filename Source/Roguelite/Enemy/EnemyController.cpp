// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

#include "Navigation/CrowdFollowingComponent.h"
#include "Roguelite/HexGameplayTags.h"
#include "Roguelite/Room/EncounterManager.h"


// Sets default values
AEnemyController::AEnemyController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StateTreeAIComponent = CreateDefaultSubobject<UStateTreeAIComponent>(TEXT("State Tree AI Component"));
	bStartAILogicOnPossess = false;
	StateTreeAIComponent -> SetStartLogicAutomatically(false);
	
	UCrowdFollowingComponent* CrowdFollowingComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());
	if (CrowdFollowingComponent)
	{
		CrowdFollowingComponent -> SetCrowdSeparation(true);
		CrowdFollowingComponent -> SetCrowdSeparationWeight(3.f);
		CrowdFollowingComponent -> SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);
		CrowdFollowingComponent -> SetCrowdOptimizeVisibility(true);
		CrowdFollowingComponent -> SetCrowdPathOptimizationRange(3500.f);
	}
	
}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyController::OnPlayerPositionDrift()
{
	StateTreeAIComponent -> SendStateTreeEvent(TAG_Encounter_PlayerReposition.GetTag());	
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (not StateTreeAIComponent)
	{
		return;
	}
	StateTreeAIComponent -> StartLogic();
	
}

void AEnemyController::OnUnPossess()
{
	Super::OnUnPossess();
	
	PlayerPositionDriftedDelegate.Remove(OnPlayerPositionDriftDelegateHandle);
}

