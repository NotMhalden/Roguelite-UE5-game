// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "STTask_ChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELITE_API USTTask_ChasePlayer : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()
	
	
public:
	USTTask_ChasePlayer(const FObjectInitializer& ObjectInitializer);
	
	
protected:
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) override;
	
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override;
};
