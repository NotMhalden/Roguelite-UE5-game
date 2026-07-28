// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CompanyDataAsset.generated.h"

class UAugmentDataAsset;
/**
 * 
 */
UCLASS(DisplayName="Company")
class ROGUELITE_API UCompanyDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Company")
	FText AugmentDisplayName;
	
	UPROPERTY(EditAnywhere, Category = "Company")
	TArray<TObjectPtr<UAugmentDataAsset>> Augments;
};
