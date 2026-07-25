// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WalkingEnemy.generated.h"

class UFloatingPawnMovement;

UCLASS()
class ROGUELITE_API AWalkingEnemy : public AEnemyCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWalkingEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void ApplyChanges() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = "true", ClampMin = "0"))
	float MaxSpeed = 800.f;	
	
};
