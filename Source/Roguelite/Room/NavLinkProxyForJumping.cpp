// Fill out your copyright notice in the Description page of Project Settings.


#include "NavLinkProxyForJumping.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Roguelite/Enemy/EnemyCharacter.h"


// Sets default values
ANavLinkProxyForJumping::ANavLinkProxyForJumping()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANavLinkProxyForJumping::BeginPlay()
{
	Super::BeginPlay();
	
	OnSmartLinkReached.AddDynamic(this, &ANavLinkProxyForJumping::OnActorReachedLinkPointHandler);
}

// Called every frame
void ANavLinkProxyForJumping::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANavLinkProxyForJumping::OnActorReachedLinkPointHandler(AActor* MovingActor, const FVector& Destination)
{
	if (TObjectPtr<AEnemyCharacter> EnemyCharacter = Cast<AEnemyCharacter>(MovingActor))
	{
		FVector LaunchVelocity;
		
		float EnemyHalfHeight = EnemyCharacter -> GetCapsuleComponent() -> GetScaledCapsuleHalfHeight();
		FVector DestinationPoint = Destination + FVector(0.f,0.f,EnemyHalfHeight + 40.f);
		
		float RandomArc = 0.5f;
		if (DestinationPoint.Z <= EnemyCharacter -> GetActorLocation().Z) // Jump down
		{
			RandomArc = FMath::FRandRange(0.35f, 0.55f);
		}
		else // Jump up
		{
			RandomArc = FMath::FRandRange(0.25f, 0.35f);
		}
		
		
		if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(
					this, 
					LaunchVelocity, 
					EnemyCharacter -> GetActorLocation(), 
					DestinationPoint,
					0.f,
					RandomArc))
		{
			EnemyCharacter -> LaunchCharacter(LaunchVelocity, true, true);
			EnemyCharacter -> ActiveJumpLink = this;
		}
		else
		{
			ResumePathFollowing(EnemyCharacter);
		}
	}
}

