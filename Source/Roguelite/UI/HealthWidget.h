// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

class UTextBlock;
class UProgressBar;



/**
 * 
 */
UCLASS()
class ROGUELITE_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void OnPlayerHealthChanged(int PlayerCurrentHealth, int PlayerMaxHealth);
	
protected:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UTextBlock> CurrentHealthText;

};
