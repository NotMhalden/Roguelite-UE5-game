// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "RoomMover.generated.h"

class UBoxComponent;

UCLASS()
class ROGUELITE_API ARoomMover : public AActor, public  IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARoomMover();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(APlayerCharacter* PlayerInteractor) override;
		
protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* TriggerBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Run")
	TSoftObjectPtr<UWorld> LevelToLoad = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Run")
	bool bDoorIsOpen = false;
};
