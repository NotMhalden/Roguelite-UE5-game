// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RoomMover.h"
#include "RunStarter.generated.h"

class UBoxComponent;

UCLASS()
class ROGUELITE_API ARunStarter : public ARoomMover
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARunStarter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(APlayerCharacter* PlayerInteractor) override;

};
