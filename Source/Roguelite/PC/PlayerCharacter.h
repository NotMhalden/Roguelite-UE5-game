// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Roguelite/Weapon/HitscanWeapon.h"
#include "PlayerCharacter.generated.h"

class APCController;

UCLASS()
class ROGUELITE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TSubclassOf<APCController> PPControllerClass = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WeaponPoint = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera = nullptr;
	
public:
	// Current design allows for 1 weapon. 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	AHitscanWeapon* CurrentWeapon = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AHitscanWeapon> StartingWeapon = nullptr;
	
protected:
	bool bIsDashing = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Dash", meta = (AllowPrivateAccess = "true", ClampMin = "0.01"))
	float DashPower = 10.f;
	
	FTimerHandle DashDelayTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Dash", meta = (AllowPrivateAccess = "true", ClampMin = "0.01"))
	float DashDelay = 0.5f;
	void DashDelayOver();
	
public:
	void MainAction();
	
	void Dash(const FInputActionValue& Value);
	
	
};
