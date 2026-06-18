// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "PCController.generated.h"

class APlayerCharacter;



/**
 * 
 */
UCLASS()
class ROGUELITE_API APCController : public APlayerController
{
	GENERATED_BODY()
public:
	APCController();
	
	UPROPERTY()
	TObjectPtr<APlayerCharacter> FPSCharacter;
	
protected:
	virtual void SetupInputComponent() override;
	
	virtual void OnPossess(APawn* InPawn) override;
	

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	void JumpStart();
	void JumpEnd();
	
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> MainIMC;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IAMovement = nullptr;	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IALook = nullptr;	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IAJump = nullptr;
	
};
