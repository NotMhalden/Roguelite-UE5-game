// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "HitscanWeapon.generated.h"



DECLARE_MULTICAST_DELEGATE_OneParam(FGetCameraForwardVectorDelegate, FVector /*CameraForwardVector */);

inline FGetCameraForwardVectorDelegate GetCameraForwardVectorDelegate;

UCLASS()
class ROGUELITE_API AHitscanWeapon : public AWeaponBase
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
	virtual void MainAttack(FVector CameraForwardVector, FVector CameraLocation) override;

protected:
	//ray casting for shooting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Camera;
};
