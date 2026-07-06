// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavAreas/NavArea_Default.h"
#include "NavArea_Jump_Default.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELITE_API UNavArea_Jump_Default : public UNavArea_Default
{
	GENERATED_BODY()
	
public:
	UNavArea_Jump_Default()
	{
		DefaultCost = 1.f;
		FixedAreaEnteringCost = 700.f;
	}
};
