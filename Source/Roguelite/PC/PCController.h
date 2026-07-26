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
	
	virtual void BeginPlay() override;
	
	
	UPROPERTY()
	TObjectPtr<APlayerCharacter> FPSCharacter;
	
protected:
	virtual void SetupInputComponent() override;
	
	virtual void OnPossess(APawn* InPawn) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Mouse", meta = (AllowPrivateAccess = "true", ClampMin = "0.01", ClampMax = "100.0"))
	float HorizontalSensitivity = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Mouse", meta = (AllowPrivateAccess = "true", ClampMin = "0.01", ClampMax = "100.0"))
	float VerticalSensitivity = 1.f;
	
public:
	virtual void AddYawInput(float Val) override;
	virtual void AddPitchInput(float Val) override;
	
protected:

	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> MainIMC;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IAMovement = nullptr;	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IALook = nullptr;	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IAJump = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IADash = nullptr;
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IAMainAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IASecondaryAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IAMeleeAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IAInteract = nullptr;
	
protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	void JumpStart();
	void JumpEnd();
	
	void Dash(const FInputActionValue& Value);
	
	void MainAction();
	void SecondaryAction();
	
	void MeleeAction();
	
	void Interact();
};
