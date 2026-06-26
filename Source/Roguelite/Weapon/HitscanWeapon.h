// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitscanWeapon.generated.h"



DECLARE_MULTICAST_DELEGATE_OneParam(FGetCameraForwardVectorDelegate, FVector /*CameraForwardVector */);

inline FGetCameraForwardVectorDelegate GetCameraForwardVectorDelegate;

UCLASS()
class ROGUELITE_API AHitscanWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitscanWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
public:
	virtual void MainAction(FVector CameraForwardVector, FVector CameraLocation);
	
	void FireRateDelayOver();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true", ClampMax = "15.0"))
	int32 Damage = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true", ClampMax = "15.0"))
	float AttackRate = 10;
	
	
protected:
	FTimerHandle AttackRateTimerHandle;
	bool bWeaponCooling = false;
	float AttackRateCooldown = 0.1f;
	
	//ray casting for shooting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;
};
