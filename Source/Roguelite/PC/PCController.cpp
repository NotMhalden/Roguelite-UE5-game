// Fill out your copyright notice in the Description page of Project Settings.


#include "PCController.h"

#include "PlayerCharacter.h"

APCController::APCController()
{
}


void APCController::SetupInputComponent()
{
	Super::SetupInputComponent();
	

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSybsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (not EnhancedInputSybsystem)
	{
		
	}
	
	// Clear
	EnhancedInputSybsystem -> ClearAllMappings();
	EnhancedInputSybsystem -> AddMappingContext(MainIMC, 0);
	
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (not EnhancedInputComponent)
	{
		return;
	}
	
	// Set up user input
	EnhancedInputComponent -> BindAction(IAMovement.Get(), ETriggerEvent::Triggered, this, &APCController::Move);
	
	EnhancedInputComponent -> BindAction(IALook.Get(), ETriggerEvent::Triggered, this, &APCController::Look);
	
	
	EnhancedInputComponent -> BindAction(IAJump.Get(), ETriggerEvent::Started, this, &APCController::JumpStart);
	EnhancedInputComponent -> BindAction(IAJump.Get(), ETriggerEvent::Completed, this, &APCController::JumpEnd);
}



void APCController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	FPSCharacter = Cast<APlayerCharacter>(InPawn);
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if (InputLocalPlayerSubsystem)
	{
		InputLocalPlayerSubsystem -> AddMappingContext(MainIMC.Get(), 0);
		return;
	}
}



void APCController::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	FPSCharacter -> AddMovementInput(ForwardDirection, MovementVector.X);
	FPSCharacter -> AddMovementInput(RightDirection, MovementVector.Y);
}



void APCController::Look(const FInputActionValue& Value)
{
	const FVector2d LookAxisVector = Value.Get<FVector2d>();
	
	FPSCharacter -> AddControllerYawInput(LookAxisVector.X);
	FPSCharacter -> AddControllerPitchInput(-LookAxisVector.Y);
}



void APCController::JumpStart()
{
	FPSCharacter -> Jump();
}

void APCController::JumpEnd()
{
	FPSCharacter -> StopJumping();
}
