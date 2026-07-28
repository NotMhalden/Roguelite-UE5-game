// Fill out your copyright notice in the Description page of Project Settings.


#include "AugmentDataAsset.h"
#include "AugmentEffectBase.h"

FActiveAugment::FActiveAugment(UAugmentDataAsset* InAugmentDefinition, UObject* InOuter)
: AugmentDefinition(InAugmentDefinition)
{
	if (not InAugmentDefinition or not InOuter)
		return;

	for (const TObjectPtr<UAugmentEffectBase>& CurrentAugmentEffect : InAugmentDefinition->AugmentEffects)
	{
		if (CurrentAugmentEffect)
			AugmentEffects.Add(DuplicateObject<UAugmentEffectBase>(CurrentAugmentEffect, InOuter));
	}
}
