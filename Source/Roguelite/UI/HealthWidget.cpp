// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UHealthWidget::OnPlayerHealthChanged(int PlayerCurrentHealth, int PlayerMaxHealth)
{
	
	CurrentHealthText -> SetText(FText::AsNumber(PlayerCurrentHealth));
	HealthBar -> SetPercent(static_cast<float>(PlayerCurrentHealth) / static_cast<float>(PlayerMaxHealth));
}