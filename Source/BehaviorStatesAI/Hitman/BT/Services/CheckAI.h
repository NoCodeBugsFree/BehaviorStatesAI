// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CheckAI.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORSTATESAI_API UCheckAI : public UBTService
{
	GENERATED_BODY()
	
private:

	UCheckAI();

	/** update next tick interval
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	// -----------------------------------------------------------------------------------

	/** current state of the AI  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector AIState;

	/** last crime location  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector LastCrimeLocation;

	/** last armed Hitman location  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector LastHitmanLocation;

	/** Hitman itself (valid if we are seeing him right now and vice versa)  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector Hitman;

	/** Armed Hitman itself (valid if we are seeing him right now and vice versa)  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector ArmedHitman;

	/** shows whether we saw crime or not  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector SawCrime;
	
	/** shows whether we see trespasser or not  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector Trespasser;

	/** cached found Hitman reference  */
	UPROPERTY(Transient)
	class AHitman* CachedHitman;

	/** cached found Armed Hitman reference  */
	UPROPERTY(Transient)
	class AHitman* CacheArmedHitman;
};
