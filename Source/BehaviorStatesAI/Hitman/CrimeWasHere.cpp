// Fill out your copyright notice in the Description page of Project Settings.

#include "CrimeWasHere.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACrimeWasHere::ACrimeWasHere()
{
	/** AI Perception Stimuli Source Component  */
	AIPerceptionStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSource"));

	/* projectile movement component  */
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 1000.f;
	ProjectileMovementComponent->MaxSpeed = 1000.f;
}

void ACrimeWasHere::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AIPerceptionStimuliSource->RegisterForSense(UAISense_Sight::StaticClass());
	AIPerceptionStimuliSource->RegisterWithPerceptionSystem();
}
