// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FindRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORSTATESAI_API UFindRandomLocation : public UBTService
{
	GENERATED_BODY()
	
private:

	UFindRandomLocation();
	
	/** update next tick interval
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	/** random reachable location on the map  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector LocationToGo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float Min = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float Max = 5000.f;
};
