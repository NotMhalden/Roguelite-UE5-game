// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HexHUD.generated.h"


class UHealthWidget;


/**
 * 
 */
UCLASS()
class ROGUELITE_API AHexHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHealthWidget> HealthWidgetClass = nullptr;
	UPROPERTY()
	TObjectPtr<UHealthWidget> HealthWidget = nullptr;
};
