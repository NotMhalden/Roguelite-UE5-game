// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "Roguelite/Enemy/EnemyPawn.h"
#include "STTask_MoveToRandomLocation.generated.h"


/**
 *
 */
UCLASS()
class ROGUELITE_API USTTask_MoveToRandomLocation : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	USTTask_MoveToRandomLocation(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AEnemyPawn> InEnemy = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AAIController> AIController = nullptr;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float RandomLocationMaxDistance = 1500.f;

protected:
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) override;
	
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override;
	
};
