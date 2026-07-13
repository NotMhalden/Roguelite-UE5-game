// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/Object.h"
#include "EnemyAttack.generated.h"


class AEnemyCharacter;



// Currently un-used, but could be used for token system
UENUM(BlueprintType)
enum class EAttackType: uint8
{
	EAT_Shooting UMETA(DisplayName = "Shooting"),
	EAT_Melee UMETA(DisplayName = "Melee")
};

/**
 * 
 */
UCLASS(Abstract, EditInlineNew)
class ROGUELITE_API UEnemyAttack : public UObject
{
	GENERATED_BODY()
	
public:
	UEnemyAttack();
	virtual bool Begin(AEnemyCharacter* Self, AActor* TargetActor);
	virtual bool Tick(AEnemyCharacter* Self, AActor* TargetActor, float DeltaTime);
	virtual int32 Score(AEnemyCharacter* Self, AActor* TargetActor);
	
	int32 GetTokenCost();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AttackData", meta = (AllowPrivateAccess = "true"))
	int32 TokenCost = 1;
	
	EAttackType AttackType;
};
