// Fill out your copyright notice in the Description page of Project Settings.


#include "PCController.h"

#include "PlayerCharacter.h"
#include "Roguelite/Weapon/Weapon.h"

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
	
	EnhancedInputComponent -> BindAction(IADash.Get(), ETriggerEvent::Triggered, this, &APCController::Dash);
	
	EnhancedInputComponent -> BindAction(IAShoot.Get(), ETriggerEvent::Triggered, this, &APCController::Shoot);
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



void APCController::AddYawInput(float Val)
{
	Super::AddYawInput(Val * HorizontalSensitivity);
}

void APCController::AddPitchInput(float Val)
{
	Super::AddPitchInput(Val * VerticalSensitivity);
}

void APCController::DashDelayOver()
{
	bIsDashing = false;
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


void APCController::Dash(const FInputActionValue& Value)
{
	if (not bIsDashing)
	{
		bIsDashing = true;
		
		FVector CurrentVelocity = FPSCharacter -> GetVelocity();
		CurrentVelocity = FVector(CurrentVelocity.X * DashPower, CurrentVelocity.Y * DashPower, 0);
		FPSCharacter -> LaunchCharacter(CurrentVelocity, false, false);
		
		GetWorldTimerManager().SetTimer(DashDelayTimerHandle, this, &APCController::DashDelayOver, DashDelay, false);
	}
}

void APCController::Shoot()
{
	FPSCharacter -> Shoot();
}

