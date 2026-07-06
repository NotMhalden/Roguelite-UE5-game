// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavArea_Jump_Default.h"
#include "NavArea_Jump_LowCost.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELITE_API UNavArea_Jump_LowCost : public UNavArea_Jump_Default
{
	GENERATED_BODY()
	
public:
	UNavArea_Jump_LowCost()
	{
		DefaultCost = 1.f;
		FixedAreaEnteringCost = 200.f;
	}
};
