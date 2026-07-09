// Fill out your copyright notice in the Description page of Project Settings.


#include "PCController.h"

#include "PlayerCharacter.h"
#include "Engine/Engine.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/GameUserSettings.h"
#include "Roguelite/Weapon/HitscanWeapon.h"

APCController::APCController()
{
}

void APCController::BeginPlay()
{
	Super::BeginPlay();
	
	UGameUserSettings* Settings = GEngine->GetGameUserSettings();
	Settings->SetOverallScalabilityLevel(1);   // Medium
	Settings->ApplySettings(false);
}


void APCController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	

	UEnhancedInputLocalPlayerSubsystem* InputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (not InputLocalPlayerSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enhanced input system failed"))
		return;
	}
	
	// Clear
	InputLocalPlayerSubsystem -> ClearAllMappings();
	InputLocalPlayerSubsystem -> AddMappingContext(MainIMC, 0);
	
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (not EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enhanced input component failed"))
		return;
	}
	
	// Set up user input
	EnhancedInputComponent -> BindAction(IAMovement.Get(), ETriggerEvent::Triggered, this, &APCController::Move);
	
	EnhancedInputComponent -> BindAction(IALook.Get(), ETriggerEvent::Triggered, this, &APCController::Look);
	
	EnhancedInputComponent -> BindAction(IAJump.Get(), ETriggerEvent::Started, this, &APCController::JumpStart);
	EnhancedInputComponent -> BindAction(IAJump.Get(), ETriggerEvent::Completed, this, &APCController::JumpEnd);
	
	EnhancedInputComponent -> BindAction(IADash.Get(), ETriggerEvent::Triggered, this, &APCController::Dash);
	
	EnhancedInputComponent -> BindAction(IAMainAction.Get(), ETriggerEvent::Triggered, this, &APCController::MainAction);
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
	FPSCharacter -> Dash(Value);
}

void APCController::MainAction()
{
	FPSCharacter -> MainAction();
}

