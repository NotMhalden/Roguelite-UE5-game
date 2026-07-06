// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavArea_Jump_Default.h"
#include "NavArea_Jump_HighCost.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELITE_API UNavArea_Jump_HighCost : public UNavArea_Jump_Default
{
	GENERATED_BODY()
public:
	UNavArea_Jump_HighCost()
	{
		DefaultCost = 1.5f;
		FixedAreaEnteringCost = 1000.f;
	}
};
