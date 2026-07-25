// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Roguelite/Enemy/WalkingEnemy.h"
#include "BigTankyShooter.generated.h"

UCLASS()
class ROGUELITE_API ABigTankyShooter : public AWalkingEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABigTankyShooter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
