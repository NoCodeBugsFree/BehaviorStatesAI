// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorStatesAI.h"
#include "BaseCharacter.generated.h"

UCLASS()
class BEHAVIORSTATESAI_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

	/** AI Perception Stimuli Source Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSource;
	
public:
	
	ABaseCharacter();

	virtual void Tick(float DeltaTime) override;
	
	/** Apply damage to this actor. */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	/** called to toggle movement mode to new made and vice versa  */
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void ToggleMovementMode(EHitmanMovementMode NewMovementMode);

	/** called to set new movement mode and adjust movement speed */
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void SetMovementMode(EHitmanMovementMode NewMovementMode);

	/** called to fire */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "AAA")
	void Fire();
	
	/**
	* Called when this Pawn is possessed. Only called on the server (or in standalone).
	*	@param C The controller possessing this pawn
	*/
	virtual void PossessedBy(AController* NewController) override;

	/** with that AI state this AI should start the game */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	EHitmanAIState AIState = EHitmanAIState::HAS_Wander;

	/** cached AI state (at begin play) for further use */
	UPROPERTY(BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	EHitmanAIState InitialAIState = EHitmanAIState::HAS_Idle;

	/** AI state when it saw a crime */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	EHitmanAIState OnDetectCrimeState = EHitmanAIState::HAS_Panic;
	
protected:

	virtual void PostInitializeComponents() override;
	
	virtual void BeginPlay() override;

	/** called whenever move state is changed to adjust MaxWalkSpeed  */
	void AdjustMovementAccordingMovingMode();

	/** called to kill and ragdoll this character */
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void Kill();

	// -----------------------------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float JogSpeed = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float SpringSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float CrouchSpeed = 100.f;

	/** shows whether character is dead or alive */
	UPROPERTY(BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	uint32 bDead : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float Health = 100.f;

	/** shows whether character is armed or not */
	UPROPERTY(BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	uint32 bArmed : 1;

	/** shows whether is located in not supposed to him area */
	UPROPERTY(BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	uint32 bTrespasser : 1;

	/** shows whether character was jumped last frame or not */
	UPROPERTY(BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	uint32 bJumpedLastFrame : 1;

	/** current aim pitch to update animation  */
	UPROPERTY(BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float AimPitch;

	/** movement mode */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	EHitmanMovementMode HitmanMovementMode = EHitmanMovementMode::HMM_Walk;
	
	/** Patrol path for AI, if nullptr - it starts wander */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	class APatrolPath* PatrolPath;

	/** hide place for this AI to hide if it saw armed Hitman or crime */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	class AActor* HidePlace;

	/** AI controller cached reference  */
	UPROPERTY(Transient, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	class AAIC* AIC;

public:	
	
	/** returns whether character is dead or not **/
	FORCEINLINE bool IsDead() const { return bDead; }
	/** shows whether is located in not supposed to him area */
	FORCEINLINE bool IsTrespasser() const { return bTrespasser; }
	/** returns whether character is dead or not **/
	FORCEINLINE bool IsArmed() const { return bArmed; }
	/** returns whether character was jumped last frame or not **/
	FORCEINLINE bool IsJumpedLastFrame() const { return bJumpedLastFrame; }
	/** returns current aim pitch **/
	FORCEINLINE float GetAimPitch() const { return AimPitch; }
	/** returns patrol path **/
	FORCEINLINE class APatrolPath* GetPatrolPath() const { return PatrolPath; }
	/** returns hidden place **/
	FORCEINLINE class AActor* GetHidePlace() const { return HidePlace; }
	/** returns AI controller reference **/
	FORCEINLINE class AAIC* GetAIC() const { return AIC; }
};
