// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RewardBase.h"
#include "MaxHealthReward.generated.h"

UCLASS()
class ROGUELITE_API AMaxHealthReward : public ARewardBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMaxHealthReward();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(APlayerCharacter* PlayerInteractor) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Encounter", meta = (AllowPrivateAccess = "true", ClampMin = 1))
	int32 MaxHealthToGive = 10;
	
};
