// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "TellAboutCrime.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORSTATESAI_API UTellAboutCrime : public UBTService
{
	GENERATED_BODY()
	
private:

	UTellAboutCrime();

	/** update next tick interval
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector LastCrimeLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector LastHitmanLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector SawCrime;
	
};
