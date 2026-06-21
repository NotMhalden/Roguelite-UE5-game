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
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Mouse", meta = (AllowPrivateAccess = "true", ClampMin = "0.01", ClampMax = "100.0"))
	float HorizontalSensitivity = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Mouse", meta = (AllowPrivateAccess = "true", ClampMin = "0.01", ClampMax = "100.0"))
	float VerticalSensitivity = 1.f;
	
public:
	virtual void AddYawInput(float Val) override;
	virtual void AddPitchInput(float Val) override;
	
protected:
	bool bIsDashing = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Dash", meta = (AllowPrivateAccess = "true", ClampMin = "0.01"))
	float DashPower = 10.f;
	
	FTimerHandle DashDelayTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Dash", meta = (AllowPrivateAccess = "true", ClampMin = "0.01"))
	float DashDelay = 0.5f;
	void DashDelayOver();
	
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
	TObjectPtr<UInputAction> IAShoot = nullptr;
	
protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	void JumpStart();
	void JumpEnd();
	
	void Dash(const FInputActionValue& Value);
	
	void Shoot();
};
