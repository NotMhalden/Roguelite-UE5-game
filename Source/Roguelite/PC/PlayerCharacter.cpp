// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Roguelite/Weapon/HitscanWeapon.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	WeaponPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Point"));
	WeaponPoint -> SetupAttachment(GetRootComponent());
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera -> SetupAttachment(GetRootComponent());
	
	GetMesh() -> SetCanEverAffectNavigation(true);
	GetCapsuleComponent() -> SetCanEverAffectNavigation(true);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
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
		
		CurrentWeapon = GetWorld() -> SpawnActor<AHitscanWeapon>(StartingWeapon, Location, Rotation);
		
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);
		CurrentWeapon -> AttachToComponent(Camera, AttachmentRules);
	}
	
}




void APlayerCharacter::MainAction()
{
	if (not CurrentWeapon)
	{
		return;
	}
	// UE_LOG(LogTemp, Warning, TEXT("Player shoots"));
	CurrentWeapon -> MainAction(Camera -> GetForwardVector(), Camera -> GetComponentLocation());
}



void APlayerCharacter::Dash(const FInputActionValue& Value)
{
	if (not bIsDashing)
	{
		bIsDashing = true;
		
		FVector CurrentVelocity = GetVelocity();
		CurrentVelocity = FVector(CurrentVelocity.X * DashPower, CurrentVelocity.Y * DashPower, 0);
		LaunchCharacter(CurrentVelocity, false, false);
		
		GetWorldTimerManager().SetTimer(DashDelayTimerHandle, this, &APlayerCharacter::DashDelayOver, DashDelay, false);
	}
}

void APlayerCharacter::DashDelayOver()
{
	bIsDashing = false;
}


void APlayerCharacter::SetHealth(int32 NewHealth)
{
	Health = NewHealth;
}



int32 APlayerCharacter::GetHealth()
{
	return Health;
}



void APlayerCharacter::SetMaxHealth(int32 NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
}



int32 APlayerCharacter::GetMaxHealth()
{
	return MaxHealth;
}



void APlayerCharacter::TakeDamage(int32 NewHealth)
{
	SetHealth(GetHealth() - NewHealth);
}



void APlayerCharacter::Death()
{
}
