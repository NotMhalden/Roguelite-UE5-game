// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "Roguelite/Enemy/EnemyCharacter.h"
#include "Roguelite/Enemy/EnemyController.h"
#include "STTask_Attack.generated.h"




USTRUCT()
struct FAttackTaskData
{
	GENERATED_BODY()
	

};



/**
 * 
 */
UCLASS(DisplayName = "Attack")
class ROGUELITE_API USTTask_Attack : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()
	
public:
	USTTask_Attack(const FObjectInitializer& ObjectInitializer);
	
	
protected:
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) override;
	
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override;
	
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	
	TObjectPtr<UEnemyAttackBase> SelectBestAttack();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AEnemyCharacter> Enemy = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AEnemyController> EnemyController = nullptr;
	
	UPROPERTY()
	TObjectPtr<UEnemyAttackBase> CurrentAttack = nullptr;
};
