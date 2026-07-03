// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Navigation/NavLinkProxy.h"
#include "EnemyCharacter.generated.h"

class AEncounterManager;



UENUM(BlueprintType)
enum class EEnemyElevationPositioning: uint8
{
	EEEP_LowBelow		UMETA(DisplayName="Low Below"),
	EEEP_Below			UMETA(DisplayName="Below"),
	EEEP_SameLevel		UMETA(DisplayName="Same Level"),
	EEEP_Above			UMETA(DisplayName="Above"),
	EEEP_HighAbove		UMETA(DisplayName="High Above"),
	EEEP_Any			UMETA(DisplayName="Any")
};



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
	virtual void Landed(const FHitResult& Hit) override;

	
	void TakeDamage(int DamageTaken);
	void Death();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = "true", ClampMin = "0"))
	int32 MaxHealth = 75;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = "true", ClampMin = "0"))
	int32 Health = MaxHealth;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AEncounterManager> EncounterManager = nullptr;
	
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = "true", 
		ClampMin = "0", ClampMax = "100", UIMin = "0", UIMax = "100"))
	TMap<EEnemyElevationPositioning, int32> EnemyPositioningNurtureChance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = "true"))
	EEnemyElevationPositioning CurrentPositioning = EEnemyElevationPositioning::EEEP_SameLevel;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = "true",
		ClampMin = "0", UIMin = "0"))
	float IdealDistance = 1400.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = "true",
	ClampMin = "0", UIMin = "0"))
	float DistancePlateau = IdealDistance/8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = "true",
	ClampMin = "0", UIMin = "0"))
	float DistanceFalloff = IdealDistance/4;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = "true",
	ClampMin = "0", UIMin = "0"))
	float TravelDistanceFalloff = 250.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = "true",
	ClampMin = "0", UIMin = "0"))
	float PlayerToPathDistanceFalloff = 400.f;
	
	
	TWeakObjectPtr<ANavLinkProxy> ActiveJumpLink = nullptr;
};
