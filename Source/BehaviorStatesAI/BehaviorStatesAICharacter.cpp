// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BehaviorStatesAICharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// ABehaviorStatesAICharacter

ABehaviorStatesAICharacter::ABehaviorStatesAICharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ABehaviorStatesAICharacter::BeginPlay()
{
	Super::BeginPlay();

	/** called whenever move state is changed to adjust MaxWalkSpeed  */
	SetMaxWalkSpeedAccordingMoveState();
}

void ABehaviorStatesAICharacter::SetMaxWalkSpeedAccordingMoveState()
{
	switch (MyMovementMode)
	{
	case EMyMovementMode::MMM_Jog:
		GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
		break;

	case EMyMovementMode::MMM_Sprint:
		GetCharacterMovement()->MaxWalkSpeed = SpringSpeed;
		break;

	case EMyMovementMode::MMM_Walk:
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		break;

	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABehaviorStatesAICharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	/** jump  */
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	/** movement  */
	PlayerInputComponent->BindAxis("MoveForward", this, &ABehaviorStatesAICharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABehaviorStatesAICharacter::MoveRight);

	/** turn  */
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	/** walk / sprint  */
	PlayerInputComponent->BindAction("ToggleJog", IE_Pressed, this, &ABehaviorStatesAICharacter::Walk);
	PlayerInputComponent->BindAction("ToggleSprint", IE_Pressed, this, &ABehaviorStatesAICharacter::Sprint);
}

void ABehaviorStatesAICharacter::Walk()
{
	/** flipflop Jog and Walk  */
	if (MyMovementMode == EMyMovementMode::MMM_Jog)
	{
		MyMovementMode = EMyMovementMode::MMM_Walk;
	}
	else
	{
		MyMovementMode = EMyMovementMode::MMM_Jog;
	}

	SetMaxWalkSpeedAccordingMoveState();
}

void ABehaviorStatesAICharacter::Sprint()
{
	/** flipflop Jog and sprint  */
	if (MyMovementMode == EMyMovementMode::MMM_Sprint)
	{
		MyMovementMode = EMyMovementMode::MMM_Jog;
	}
	else
	{
		MyMovementMode = EMyMovementMode::MMM_Sprint;
	}
	SetMaxWalkSpeedAccordingMoveState();
}

void ABehaviorStatesAICharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABehaviorStatesAICharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
