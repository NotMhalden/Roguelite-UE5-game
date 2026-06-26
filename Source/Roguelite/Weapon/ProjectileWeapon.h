// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HitscanWeapon.h"
#include "ProjectileWeapon.generated.h"

class ABullet;


UCLASS()
class ROGUELITE_API AProjectileWeapon : public AHitscanWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	virtual void MainAction(FVector CameraForwardVector, FVector CameraLocation) override;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABullet> BulletClass = nullptr;
};
