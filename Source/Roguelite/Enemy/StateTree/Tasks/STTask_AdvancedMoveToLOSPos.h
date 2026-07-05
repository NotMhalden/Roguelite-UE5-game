// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "Roguelite/Enemy/EnemyCharacter.h"
#include "Roguelite/Enemy/EnemyController.h"
#include "STTask_AdvancedMoveToLOSPos.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELITE_API USTTask_AdvancedMoveToLOSPos : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()
	
public:
	USTTask_AdvancedMoveToLOSPos(const FObjectInitializer& ObjectInitializer);
	
	
protected:
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) override;
	
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AEnemyCharacter> Enemy = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AEnemyController> EnemyController = nullptr;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Parameter", meta = (AllowPrivateAccess = "true"))
	float MaxCheckDistance = 2500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Parameter", meta = (AllowPrivateAccess = "true"))
	float MinimumRangeToPlayer = 600.f;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Parameter", meta = (AllowPrivateAccess = "true"))
	int32 AttemptsToCheck = 25;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Parameter", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Camera;
};
