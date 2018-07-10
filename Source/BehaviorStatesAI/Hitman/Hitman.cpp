// Fill out your copyright notice in the Description page of Project Settings.

#include "Hitman.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AHitman::AHitman()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 160.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, 60.f));

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	FollowCamera->SetRelativeLocation(FVector(0.f, 60.f, 0.f));

	/* sphere collision  */
	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	InteractionSphere->SetupAttachment(RootComponent);
	InteractionSphere->SetSphereRadius(200.f);

	InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionSphere->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
}

// Called when the game starts or when spawned
void AHitman::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHitman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/** called to make some noise if we move to fast */
	MakeMovementNoise();

	/** weapon pitch  */
	AimPitch = FollowCamera->GetComponentRotation().Pitch;
}

void AHitman::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	bJumpedLastFrame = false;

	/** make landed noise  */
	PawnMakeNoise(1.f, GetActorLocation(), true, this);
}

void AHitman::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();

	bJumpedLastFrame = true;
}

void AHitman::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHitman::OnOverlapBegin);
}

void AHitman::MoveForward(float Value)
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

void AHitman::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
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

void AHitman::ToggleJog()
{
	ToggleMovementMode(EHitmanMovementMode::HMM_Jog);
}

void AHitman::ToggleSprint()
{
	ToggleMovementMode(EHitmanMovementMode::HMM_Sprint);
}

void AHitman::ToggleCrouch()
{
	ToggleMovementMode(EHitmanMovementMode::HMM_Crouch);

	if (HitmanMovementMode == EHitmanMovementMode::HMM_Crouch)
	{
		Crouch();
	} 
	else
	{
		UnCrouch();
	}
}

void AHitman::MakeMovementNoise()
{
	if (HitmanMovementMode == EHitmanMovementMode::HMM_Jog || HitmanMovementMode == EHitmanMovementMode::HMM_Sprint)
	{
		float SpeedRate = GetCharacterMovement()->Velocity.Size() / GetCharacterMovement()->MaxWalkSpeed;
		bool bEnoughSpeed = SpeedRate > 0.5f;
		bool bFalling = GetCharacterMovement()->IsFalling();
		if (bEnoughSpeed && !bFalling)
		{
			PawnMakeNoise(FMath::Clamp(SpeedRate, 0.25f, 1.f), GetActorLocation(), true, this);
		}
	}
}

// Called to bind functionality to input
void AHitman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);

	/** jump  */
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	/** movement  */
	PlayerInputComponent->BindAxis("MoveForward", this, &AHitman::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHitman::MoveRight);

	/** turn  */
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	/** jog / sprint / crouch */
	PlayerInputComponent->BindAction("ToggleJog", IE_Pressed, this, &AHitman::ToggleJog);
	PlayerInputComponent->BindAction("ToggleSprint", IE_Pressed, this, &AHitman::ToggleSprint);
	PlayerInputComponent->BindAction("ToggleCrouch", IE_Pressed, this, &AHitman::ToggleCrouch);
}

void AHitman::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// Other Actor is the actor that triggered the event. Check that is not ourself. 
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		
	}
}
