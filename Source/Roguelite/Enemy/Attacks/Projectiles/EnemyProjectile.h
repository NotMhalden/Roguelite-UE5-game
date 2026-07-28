// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Roguelite/Weapon/Bullet/BulletBase.h"
#include "EnemyProjectile.generated.h"

class AEnemyCharacter;

UCLASS()
class ROGUELITE_API AEnemyProjectile : public ABulletBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnCollision(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit) override;
	
public:
	UPROPERTY()
	AEnemyCharacter* EnemyAttacker = nullptr;
};
