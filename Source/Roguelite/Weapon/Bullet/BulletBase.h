// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS(Abstract)
class ROGUELITE_API ABulletBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABulletBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	virtual void OnCollision(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile | Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile | Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile | Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> MovementComponent;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true", ClampMin = "1000.0"))
	float BulletSpeed = 500.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true", ClampMax = "15.0"))
	float BulletLifespan;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	int32 BulletDamage = 15;
};
