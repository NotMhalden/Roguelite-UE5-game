// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Roguelite/Room/Interactable.h"
#include "RewardBase.generated.h"

class USphereComponent;

UCLASS(Abstract)
class ROGUELITE_API ARewardBase : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARewardBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:
	virtual void Interact(APlayerCharacter* PlayerInteractor) override;

protected:
	UPROPERTY()
	USphereComponent* PickableSphere;
	
};
