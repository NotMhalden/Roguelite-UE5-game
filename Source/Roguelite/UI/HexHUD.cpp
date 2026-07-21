// Fill out your copyright notice in the Description page of Project Settings.


#include "HexHUD.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.h"
#include "Roguelite/PC/PlayerDelegates.h"

void AHexHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (HealthWidgetClass)
	{
		UUserWidget* CreatedWidget = CreateWidget(GetOwningPlayerController(), HealthWidgetClass);
		if (CreatedWidget)
		{
			HealthWidget = Cast<UHealthWidget>(CreatedWidget);
			if (HealthWidget)
			{
				HealthWidget -> AddToViewport();
				OnPlayerHealthChange.AddUObject(HealthWidget, &UHealthWidget::OnPlayerHealthChanged);
			}
		}
	}
	
	
}
