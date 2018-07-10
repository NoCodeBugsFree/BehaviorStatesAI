// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/** enum that describes the current state of the AI */
UENUM(BlueprintType)
enum class EHitmanAIState : uint8
{
	HAS_Idle		UMETA(DisplayName = "Idle"),
	HAS_Wander		UMETA(DisplayName = "Wander"),
	HAS_Patrolling	UMETA(DisplayName = "Patrolling"),
	HAS_Panic		UMETA(DisplayName = "Panic"),
	HAS_Vigilant	UMETA(DisplayName = "Vigilant"),
	HAS_Hostile		UMETA(DisplayName = "Hostile")
};

/** enum that describes movement mode  */
UENUM(BlueprintType)
enum class EHitmanMovementMode : uint8
{
	HMM_Walk	UMETA(DisplayName = "Walk"),
	HMM_Jog		UMETA(DisplayName = "Jog"),
	HMM_Sprint	UMETA(DisplayName = "Sprint"),
	HMM_Crouch	UMETA(DisplayName = "Crouch")
};
