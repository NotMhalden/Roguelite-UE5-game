// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Blueprint/StateTreeEvaluatorBlueprintBase.h"
#include "Roguelite/Enemy/EnemyCharacter.h"
#include "STEvaluator_CheckForPlayerUpdate.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELITE_API USTEvaluator_CheckForPlayerUpdate : public UStateTreeEvaluatorBlueprintBase
{
	GENERATED_BODY()

protected:
	virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AEnemyCharacter> Enemy = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AAIController> AIController = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DistanceToPlayer = 0.f;
};
