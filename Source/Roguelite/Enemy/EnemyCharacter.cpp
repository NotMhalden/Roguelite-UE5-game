// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent() -> InitCapsuleSize(45.0f, 90.0f);
	GetCapsuleComponent() -> SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	GetMesh() -> SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	
}


// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}




void AEnemyCharacter::TakeDamage(int DamageTaken)
{
	Health -= DamageTaken;
	if (Health <= 0)
	{
		Death();
	}
}


void AEnemyCharacter::Death()
{
	if (OnDeathDelegate.IsBound())
	{
		OnDeathDelegate.Broadcast();
	}
	Destroy();
}

