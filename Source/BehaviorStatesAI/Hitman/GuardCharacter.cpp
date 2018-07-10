// Fill out your copyright notice in the Description page of Project Settings.

#include "GuardCharacter.h"
#include "ConstructorHelpers.h"

AGuardCharacter::AGuardCharacter()
{
	/** set Guard AI controller  */
	static ConstructorHelpers::FClassFinder<AController> AIC_BPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/Hitman/AI/Core/Guard/BP_GuardAIC"));
	if (AIC_BPClass.Class)
	{
		AIControllerClass = AIC_BPClass.Class;
	}

	AIState = EHitmanAIState::HAS_Idle;
	OnDetectCrimeState = EHitmanAIState::HAS_Hostile;
}
