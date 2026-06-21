// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Bullet/Bullet.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh -> SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::Fire(FVector CameraForwardVector)
{
	if (not BulletClass)
	{
		return;
	}
	
	UWorld* const World = GetWorld();
	if (not World)
	{
		return;
	}
	
	FRotator SpawnRotation = CameraForwardVector.Rotation();
	FVector SpawnLocation = CameraForwardVector + UKismetMathLibrary::GetForwardVector(SpawnRotation) * 10.0;
	
	
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
	World -> SpawnActor<ABullet>(BulletClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
}

