// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "PlayerDelegates.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Roguelite/Weapon/HitscanWeapon.h"
#include "UObject/ReferenceChainSearch.h"

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
	
	
	JumpMaxCount = AmountOfJumps;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	if (bIsMantling)
		Mantle(DeltaTime);
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
	
	if (OnPlayerHealthChange.IsBound())
		OnPlayerHealthChange.Broadcast(Health, MaxHealth);
	
}




void APlayerCharacter::MainAction()
{
	if (not CurrentWeapon)
	{
		return;
	}
	// UE_LOG(LogTemp, Warning, TEXT("Player shoots"));
	CurrentWeapon -> MainAttack(Camera -> GetForwardVector(), Camera -> GetComponentLocation());
}



void APlayerCharacter::Dash(const FInputActionValue& Value)
{
	if (bIsDashing)
		return;
	
	bIsDashing = true;
	
	FVector CurrentVelocity = GetVelocity();
	CurrentVelocity = FVector(CurrentVelocity.X * DashPower, CurrentVelocity.Y * DashPower, 0);
	LaunchCharacter(CurrentVelocity, false, false);
	
	GetWorldTimerManager().SetTimer(DashDelayTimerHandle, this, &APlayerCharacter::DashDelayOver, DashDelay, false);
}

void APlayerCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);
	
	if (GetCharacterMovement() -> MovementMode == MOVE_Falling)
	{
		bShouldMantleCheck = true;
	}
	if (GetCharacterMovement() -> MovementMode != MOVE_Falling)
	{
		bShouldMantleCheck = false;
	}
}

void APlayerCharacter::Jump()
{
	Super::Jump();
	
}

void APlayerCharacter::StopJumping()
{
	Super::StopJumping();
}



void APlayerCharacter::MantleCheck()
{
	if (bIsMantling)
		return;
	
	const UWorld* World = GetWorld();
	if (not World)
		return;
	
	
	FVector TraceStart = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + GetCapsuleComponent() -> GetScaledCapsuleHalfHeight());
	const FVector TraceDirection = GetActorForwardVector();
	FVector TraceEnd = TraceStart + TraceDirection * MantleTraceDistance;
	
	ECollisionChannel TraceChannel = ECC_WorldStatic;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	
	// Tracing from the top of the player character
	FHitResult Hit;
	bool bDidHit = World -> LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannel, QueryParams);
	// DrawDebugLine(World, TraceStart, TraceEnd, FColor::Red, false, 2.f, 0, 1.5f);
	
	if (not bDidHit)
	{
		// Tracing from the center of the player character
		TraceStart = GetActorLocation();
		TraceEnd = TraceStart + TraceDirection * MantleTraceDistance;
		
		bDidHit = World -> LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannel, QueryParams);
		// DrawDebugLine(World, TraceStart, TraceEnd, FColor::Red, false, 2.f, 0, 1.5f);
	}
	
	if (not bDidHit)
		return;
	
	
	// Tracing from above
	FVector TopTraceStart = FVector(
		Hit.Location.X, 
		Hit.Location.Y, 
		Hit.Location.Z + MantleTraceHeight) + TraceDirection * 50;
	
	FVector TopTraceEnd = Hit.Location + TraceDirection * 50;
	
	FHitResult TopHit;
	bool bDidTopHit = World -> LineTraceSingleByChannel(TopHit, TopTraceStart, TopTraceEnd, TraceChannel, QueryParams);
	if (not bDidTopHit or TopHit.bStartPenetrating)
		return;
	
	// DrawDebugLine(World, TopTraceStart, TopTraceEnd, FColor::Purple, false, 2.f, 0, 1.5f);
	
	
	
	
	PostMantleLocation = TopHit.Location + TraceDirection * 100;
	PostMantleLocation.Z += GetCapsuleComponent() -> GetScaledCapsuleHalfHeight() + 25.f;
	
	
	FVector PlayerXMantleCorner = GetActorLocation();
	PlayerXMantleCorner.Z = PostMantleLocation.Z;
	
	
	// Pytagoras thingy. Checking edges and not the straight line
	FHitResult MantleLegCheck1Hit;
	bool bDidMantleLegCheck1Hit = World -> LineTraceSingleByChannel(MantleLegCheck1Hit, GetActorLocation(), PlayerXMantleCorner, TraceChannel, QueryParams);
	if (bDidMantleLegCheck1Hit or MantleLegCheck1Hit.bStartPenetrating)
		return;
	
	FHitResult MantleLegCheck2Hit;
	bool bDidMantleLegCheck2Hit = World -> LineTraceSingleByChannel(MantleLegCheck2Hit, PlayerXMantleCorner, PostMantleLocation, TraceChannel, QueryParams);
	if (bDidMantleLegCheck2Hit or MantleLegCheck2Hit.bStartPenetrating)
		return;
	
	
	// Checking if the player capsule fits
	const bool bDoesPlayerCollide = World -> OverlapBlockingTestByChannel(
		PostMantleLocation,
		GetActorRotation().Quaternion(), 
		ECC_Visibility, 
		GetCapsuleComponent()->GetCollisionShape(),
		QueryParams);
	
	if (bDoesPlayerCollide)
		return;
	
	
	PreMantleLocation = GetActorLocation();
	GetCharacterMovement() -> SetMovementMode(MOVE_None);
	bIsMantling = true;
}


void APlayerCharacter::Mantle(float DeltaTime)
{
	CurrentMantlingAlpha += DeltaTime / MantlingTime;
	CurrentMantleLocation = FMath::Lerp(PreMantleLocation, PostMantleLocation, CurrentMantlingAlpha);
	SetActorLocation(CurrentMantleLocation);
	
	if (CurrentMantlingAlpha >= 1.f)
		MantleFinished();
}


void APlayerCharacter::MantleFinished()
{
	SetActorLocation(PostMantleLocation);
	
	CurrentMantlingAlpha = 0.f;
	bIsMantling = false;
	GetCharacterMovement() -> SetMovementMode(MOVE_Walking);
}




void APlayerCharacter::DashDelayOver()
{
	bIsDashing = false;
}




void APlayerCharacter::SetHealth(int32 NewHealth)
{
	Health = NewHealth;
	if (OnPlayerHealthChange.IsBound())
		OnPlayerHealthChange.Broadcast(Health, MaxHealth);
}



int32 APlayerCharacter::GetHealth()
{
	return Health;
}



void APlayerCharacter::SetMaxHealth(int32 NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
	if (OnPlayerHealthChange.IsBound())
		OnPlayerHealthChange.Broadcast(Health, MaxHealth);
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
