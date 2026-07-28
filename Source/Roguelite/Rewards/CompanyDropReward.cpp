// Fill out your copyright notice in the Description page of Project Settings.


#include "CompanyDropReward.h"

#include "Roguelite/Augments/AugmentDataAsset.h"
#include "Roguelite/Augments/CompanyDataAsset.h"
#include "Roguelite/PC/PlayerCharacter.h"


// Sets default values
ACompanyDropReward::ACompanyDropReward()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACompanyDropReward::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACompanyDropReward::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACompanyDropReward::Interact(APlayerCharacter* PlayerInteractor)
{
	if (CompanyDropDataAsset.Get())
	{
		if (not CompanyDropDataAsset->Augments.IsEmpty())
		{
			int32 AugmentIndex = FMath::RandRange(0, CompanyDropDataAsset->Augments.Num()-1);
			
			if (CompanyDropDataAsset->Augments[AugmentIndex])
				PlayerInteractor -> GrantAugment(CompanyDropDataAsset->Augments[AugmentIndex]);
		}
	}
	Super::Interact(PlayerInteractor);
}

