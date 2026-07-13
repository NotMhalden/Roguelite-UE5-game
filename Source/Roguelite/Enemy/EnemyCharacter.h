// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyDelegates.h"
#include "Attacks/EnemyAttack.h"
#include "BehaviorTree/Tasks/BTTask_RunDynamicStateTree.h"
#include "GameFramework/Character.h"
#include "Navigation/NavLinkProxy.h"
#include "Navigation/PathFollowingComponent.h"
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

	UFUNCTION()
	void MovementSafetyNet();
	
	void TakeDamage(int DamageTaken);
	void Death();
	
	
	bool RequestAttack(int32 AttackCost);
	void OnAttackFinished();
	
protected:
	/**
	 * This function is called, once the token is changed.
	 * Token can bw changed if another enemy should rather have it.
	 */
	void OnTokenChange();
	
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = "true", ClampMin = "0"))
	int32 MaxHealth = 75;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (AllowPrivateAccess = "true", ClampMin = "0"))
	int32 Health = MaxHealth;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<AEncounterManager> EncounterManager = nullptr;
	
	
public:
	FOnEnemyTokenChange OnEnemyTokenChange;

	UPROPERTY(EditAnywhere, Instanced, Category = "Data|Attacks")
	TArray<UEnemyAttack*> Attacks;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|AI", meta = (AllowPrivateAccess = "true", 
		ClampMin = "0", ClampMax = "100", UIMin = "0", UIMax = "100"))
	TMap<EEnemyElevationPositioning, int32> EnemyPositioningNurtureChance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|AI", meta = (AllowPrivateAccess = "true"))
	EEnemyElevationPositioning CurrentPositioning = EEnemyElevationPositioning::EEEP_SameLevel;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|AI", meta = (AllowPrivateAccess = "true",
		ClampMin = "0", UIMin = "0"))
	float IdealDistance = 1700.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|AI", meta = (AllowPrivateAccess = "true"))
	float IdealHeightDistance = -150.f;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|AI", meta = (AllowPrivateAccess = "true"))
	float PositioningHeightThreshold = IdealHeightDistance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|AI", meta = (AllowPrivateAccess = "true",
	ClampMin = "0", UIMin = "0"))
	float DistancePlateau = IdealDistance/8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|AI", meta = (AllowPrivateAccess = "true",
	ClampMin = "0", UIMin = "0"))	
	float DistanceFalloff = IdealDistance/4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|AI", meta = (AllowPrivateAccess = "true",
	ClampMin = "0", UIMin = "0"))
	float MinimumRangeToPlayer = 600.f;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|AI", meta = (AllowPrivateAccess = "true",
	ClampMin = "0", UIMin = "0"))
	float TravelDistanceFalloff = 250.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|AI", meta = (AllowPrivateAccess = "true",
	ClampMin = "0", UIMin = "0"))
	float PlayerToPathDistanceFalloff = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|AI", meta = (AllowPrivateAccess = "true",
	ClampMin = "0", UIMin = "0"))
	float MinimumPlayerDistanceToPath = 600.f;
	
	
	TWeakObjectPtr<ANavLinkProxy> ActiveJumpLink = nullptr;
	

protected:
	FTimerHandle SafetyNetTimerHandle;
	FVector LastKnownLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|SafetyNet", meta = (AllowPrivateAccess = "true"))
	float SafetyNetActivationDistanceThreshold = 30.f;
	UPROPERTY()
	float TimeEnemyStuck = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|SafetyNet", meta = (AllowPrivateAccess = "true"))
	float SafetyNetNudgingDistance = 20.f;
};
