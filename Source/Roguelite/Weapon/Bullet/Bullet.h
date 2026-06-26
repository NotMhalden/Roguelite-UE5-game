// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Roguelite/Weapon/HitscanWeapon.h"
#include "Bullet.generated.h"


class USphereComponent;

UCLASS()
class ROGUELITE_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile | Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile | Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile | Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> MovementComponent;
	

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true", ClampMin = "1000.0"))
	float BulletSpeed = 5500.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true", ClampMax = "15.0"))
	float BulletLifespan = 5.0f;
	
	int32 BulletDamage = 15;
};
