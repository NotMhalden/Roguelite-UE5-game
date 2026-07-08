// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeEvaluatorBase.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "STEvaluator_RunEQSQuery.generated.h"


USTRUCT()
struct FEQSEvaluatorData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<AActor> Owner = nullptr;
	
	UPROPERTY(EditAnywhere, Category="Parameter")
	TObjectPtr<UEnvQuery> EnvironmentQuery  = nullptr;
	UPROPERTY(EditAnywhere, Category="Parameter")
	TEnumAsByte<EEnvQueryRunMode::Type> EQRunMode  = EEnvQueryRunMode::SingleResult;
	
	UPROPERTY(EditAnywhere, Category="Parameter")
	float InnerRadius = 600.f;
	UPROPERTY(EditAnywhere, Category="Parameter")
	float OuterRadius = 1700.f;
	
	UPROPERTY(VisibleAnywhere, Category="Output")
	FVector OutputLocation = FVector(0.f, 0.f, 0.f);
	
	bool bInFlight = false;
	bool bHasQueried = false;
};



/**
 * 
 */
USTRUCT(DisplayName="Continuous EQS")
struct ROGUELITE_API FSTEvaluator_RunEQSQuery : public FStateTreeEvaluatorCommonBase 
{
	GENERATED_BODY()

public:
	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}
	virtual void Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
	
	
public:
	using FInstanceDataType = FEQSEvaluatorData;
	
};
