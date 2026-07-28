// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AugmentDataAsset.generated.h"


class UAugmentEffectBase;

UENUM(BlueprintType)
enum class EAugmentRarity: uint8
{
	EAR_Common				UMETA(DisplayName="Common"),
	EAR_Rare				UMETA(DisplayName="Rare"),
	EAR_Epic				UMETA(DisplayName="Epic"),
	EAR_Legendary			UMETA(DisplayName="Legendary"),
	EAR_Collaboration		UMETA(DisplayName="Collaboration")
	
};


USTRUCT(BlueprintType)
struct FActiveAugment
{
	GENERATED_BODY()
	
public:
	FActiveAugment() = default;
	FActiveAugment(UAugmentDataAsset* InAugmentDefinition, UObject* InOuter);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Augment")
	TObjectPtr<UAugmentDataAsset> AugmentDefinition;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Augment")
	EAugmentRarity AugmentRarity = EAugmentRarity::EAR_Common;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Augment")
	int32 AugmentLevel = 1;
	
	UPROPERTY(EditAnywhere, Category = "Augment")
	TArray<TObjectPtr<UAugmentEffectBase>> AugmentEffects;
};


/**
 * 
 */
UCLASS(DisplayName="Augment")
class ROGUELITE_API UAugmentDataAsset : public UDataAsset
{
	GENERATED_BODY()

	
public:
	UPROPERTY(EditAnywhere, Category = "Augment")
	FText AugmentDisplayName;
	
	UPROPERTY(EditAnywhere, Instanced, Category = "Augment")
	TArray<TObjectPtr<UAugmentEffectBase>> AugmentEffects;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Augment")
	EAugmentRarity AugmentStartingRarity = EAugmentRarity::EAR_Common;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Augment")
	int32 AugmentStartingLevel = 1;
	
public:
	/* 
	 * Put in save system once there is one. Used to define if this augment is unlocked or not
	 *
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Augment")
	bool bIsUnlocked = true;
	*/
};
