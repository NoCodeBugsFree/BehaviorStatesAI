// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorStatesAICharacter.generated.h"

/** enum that describes our character custom movement mode  */
UENUM(BlueprintType)
enum class EMyMovementMode : uint8
{
	MMM_Walk UMETA(DisplayName = "Walk"),
	MMM_Jog UMETA(DisplayName = "Jog"),
	MMM_Sprint UMETA(DisplayName = "Sprint")
};

/** enum that describes the current state of the AI */
UENUM(BlueprintType)
enum class EAIState : uint8
{
	AS_Idle UMETA(DisplayName = "Idle"),
	AS_Patrolling UMETA(DisplayName = "Patrolling"),
	AS_Suspicious UMETA(DisplayName = "Suspicious"),
	AS_Searching UMETA(DisplayName = "Searching"),
	AS_Hostile UMETA(DisplayName = "Hostile")
};

UCLASS(config=Game)
class ABehaviorStatesAICharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:

	ABehaviorStatesAICharacter();

	virtual void BeginPlay() override;
	
protected:

	/** Called for forwards/backward input */
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void MoveForward(float Value);

	/** Called for side to side input */
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void MoveRight(float Value);

protected:

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	
	/** called whenever move state is changed to adjust MaxWalkSpeed  */
	void SetMaxWalkSpeedAccordingMoveState();
	
	/** flipflop Jog and Walk  */
	void Walk();
	
	/** flipflop Jog and Sprint  */
	void Sprint();

	/** Current moment mode */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	EMyMovementMode MyMovementMode = EMyMovementMode::MMM_Jog;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float JogSpeed = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float SpringSpeed = 600.f;

	/** current AI state  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	EAIState AIState = EAIState::AS_Idle;

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

