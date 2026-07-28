// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RewardBase.h"
#include "CompanyDropReward.generated.h"


class UCompanyDataAsset;

UCLASS()
class ROGUELITE_API ACompanyDropReward : public ARewardBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACompanyDropReward();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(APlayerCharacter* PlayerInteractor) override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Company Drop")
	TObjectPtr<UCompanyDataAsset> CompanyDropDataAsset;
};
