// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "AIC.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->JumpZVelocity = 350.f;
	GetCharacterMovement()->AirControl = 0.2f;

	/** can crouch  */
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;
	GetCharacterMovement()->CrouchedHalfHeight = 60.f;

	
	// -----------------------------------------------------------------------------------

	/** AI Perception Stimuli Source Component  */
	AIPerceptionStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSource"));
	
	/** smooth rotation during patrol facing  */
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.0f, 0.0f);

	/** we need to allow AI controller to set focus to us  */
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	/** should it depend on HitmanMovementMode ?  */
	GetCharacterMovement()->MaxAcceleration = SpringSpeed;

	/** set AI controller  */
	static ConstructorHelpers::FClassFinder<AController> AIC_BPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/Hitman/AI/Core/Citizen/BP_CitizenAIC"));
	if (AIC_BPClass.Class)
	{
		AIControllerClass = AIC_BPClass.Class;
	}
}

void ABaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	AIPerceptionStimuliSource->RegisterForSense(UAISense_Sight::StaticClass());
	AIPerceptionStimuliSource->RegisterForSense(UAISense_Hearing::StaticClass());
	AIPerceptionStimuliSource->RegisterWithPerceptionSystem();
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	/** called whenever move state is changed to adjust MaxWalkSpeed  */
	AdjustMovementAccordingMovingMode();
}

void ABaseCharacter::AdjustMovementAccordingMovingMode()
{
	switch (HitmanMovementMode)
	{
	case EHitmanMovementMode::HMM_Jog:
		GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);
		break;

	case EHitmanMovementMode::HMM_Sprint:
		GetCharacterMovement()->MaxWalkSpeed = SpringSpeed;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);
		break;

	case EHitmanMovementMode::HMM_Walk:
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
		break;

	case EHitmanMovementMode::HMM_Crouch:
		GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
		break;

	default:
		break;
	}
}

void ABaseCharacter::Kill()
{
	bDead = true;

	// Kill Ragdoll Character
	if(AAIC* AIC = Cast<AAIC>(Controller))
	{
		DetachFromControllerPendingDestroy();
	}
	
	static FName CollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetCollisionProfileName(CollisionProfileName);
	
	SetActorEnableCollision(true);
	
	// rag doll  (init Physics)
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->WakeAllRigidBodies();
	GetMesh()->bBlendPhysics = true;
	
	// disable movement
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();
	GetCharacterMovement()->SetComponentTickEnabled(false);
	
	// disable collisions on the capsule
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);

	/**   */
	if(APlayerController* PC = Cast<APlayerController>(Controller))
	{
		PC->StartSpectatingOnly();
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABaseCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.f)
	{
		Health -= ActualDamage;

		/** we are under attack!  */
		if (AIC && AIC->GetBlackboardComp())
		{
			/** save the location where we was attacked  */
			AIC->GetBlackboardComp()->SetValueAsVector(FName(TEXT("LastCrimeLocation")), GetActorLocation());
			AIC->SetAIState(AIC->OnDetectCrimeState);
		}

		// If the damage depletes our health set our lifespan to zero - which will destroy the actor  
		if (Health <= 0.f)
		{
			Kill();
		}
	}
	return ActualDamage;
}

void ABaseCharacter::ToggleMovementMode(EHitmanMovementMode NewMovementMode)
{
	if (HitmanMovementMode != EHitmanMovementMode::HMM_Walk)
	{
		HitmanMovementMode = EHitmanMovementMode::HMM_Walk;
	}
	else
	{
		HitmanMovementMode = NewMovementMode;
	}

	AdjustMovementAccordingMovingMode();
}

void ABaseCharacter::SetMovementMode(EHitmanMovementMode NewMovementMode)
{
	HitmanMovementMode = NewMovementMode;
	AdjustMovementAccordingMovingMode();
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(AAIC* TestAIC = Cast<AAIC>(NewController))
	{
		AIC = TestAIC;
	}

	/** cache the initial state  */
	InitialAIState = AIState;
}

