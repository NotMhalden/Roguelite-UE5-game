// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Roguelite/Weapon/Weapon.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	WeaponPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Point"));
	WeaponPoint -> SetupAttachment(GetRootComponent());
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera -> SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
	auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APlayerController* CastPlayerController = Cast<APlayerController>(PlayerController);
	if (not CastPlayerController)
	{
		return;
	}
	
	if (StartingWeapon)
	{
		if (CurrentWeapon)
		{
			CurrentWeapon -> Destroy();
			CurrentWeapon = nullptr;
		}
		
		
		FVector Location = WeaponPoint -> GetRelativeLocation();
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		
		CurrentWeapon = GetWorld() -> SpawnActor<AWeapon>(StartingWeapon, Location, Rotation);
		
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);
		CurrentWeapon -> AttachToComponent(Camera, AttachmentRules);
	}
	
}



void APlayerCharacter::Shoot()
{
	if (not CurrentWeapon)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Player shoots"));
	CurrentWeapon -> Fire(Camera -> GetForwardVector(), Camera -> GetComponentLocation());
}




// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

