// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"


class AEncounterManager;
DECLARE_MULTICAST_DELEGATE(FOnDeathDelegate)


UCLASS(Abstract)
class ROGUELITE_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	void TakeDamage(int DamageTaken);
	void Death();
	
	
public:
	FOnDeathDelegate OnDeathDelegate;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = "true", ClampMin = "0"))
	int32 MaxHealth = 75;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = "true", ClampMin = "0"))
	int32 Health = MaxHealth;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AEncounterManager> EncounterManager = nullptr;
};
