// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "BehaviorStatesAI.h"
#include "AIC.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORSTATESAI_API AAIC : public AAIController
{
	GENERATED_BODY()

	/** AI Perception Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionComponent* AIPerceptionComponent;
	
	/** sight sense config template to our AI  */
	UPROPERTY(BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	class UAISenseConfig_Sight* Sight;
	
	/** hearing sense config template to our AI  */
	UPROPERTY(BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	class UAISenseConfig_Hearing* Hearing;

	/** Blackboard Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBlackboardComponent* BlackboardComponent;
	
	/** BehaviorTree Component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTreeComponent;
	
	/** Behavior Tree  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;
	
public:
	
	AAIC();

	virtual void Possess(APawn* Pawn) override;

	virtual void PostInitializeComponents() override;

	/** calls when AI Perception Component updated */
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	/** calls when AI Perception Component updated */
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
	/** called to set new state */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAA")
	void SetAIState(EHitmanAIState NewState);
	virtual void SetAIState_Implementation(EHitmanAIState NewState);
	
	/** called to start timer that will call SetSawCrime with delay */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void StartAttack(bool bShouldStart, float TimeToStartAttackHitman = 15.f);

	/** sets the blackboard value bSawCrime to true  */
	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetSawCrime();
	
	UPROPERTY()
	FTimerHandle AttackHitmanTimer;
	
// -----------------------------------------------------------------------------------

	/** with that AI state this AI should start the game */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	EHitmanAIState HitmanAIState = EHitmanAIState::HAS_Idle;

	/** state to set this AI when it saw a crime scene or an armed Hitman  */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	EHitmanAIState OnDetectCrimeState = EHitmanAIState::HAS_Panic;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Config")
	class ABaseCharacter* AIPawn;

public:

	FORCEINLINE class UBlackboardComponent* GetBlackboardComp() const { return BlackboardComponent; }

	FORCEINLINE class UAIPerceptionComponent* GetAIPerceptionComponent() const { return AIPerceptionComponent; }
};
