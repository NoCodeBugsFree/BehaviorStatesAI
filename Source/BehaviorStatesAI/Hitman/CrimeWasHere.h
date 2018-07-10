// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hitman/TossItem.h"
#include "CrimeWasHere.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORSTATESAI_API ACrimeWasHere : public ATossItem
{
	GENERATED_BODY()
	
	/** AI Perception Stimuli Source Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSource;

	/* projectile movement component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovementComponent;
	
public:

	ACrimeWasHere();
	
	virtual void PostInitializeComponents() override;
};
