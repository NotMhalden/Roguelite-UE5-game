// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/NavLinkProxy.h"
#include "NavLinkProxyForJumping.generated.h"

class ACharacter;

UCLASS()
class ROGUELITE_API ANavLinkProxyForJumping : public ANavLinkProxy
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANavLinkProxyForJumping();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnActorReachedLinkPointHandler(AActor* MovingActor, const FVector& Destination);

	
};
