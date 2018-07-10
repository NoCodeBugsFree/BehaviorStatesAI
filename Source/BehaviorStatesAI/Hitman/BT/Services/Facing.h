// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Facing.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORSTATESAI_API UFacing : public UBTService
{
	GENERATED_BODY()

private:

	UFacing();

	/** called when auxiliary node becomes active
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	/** called when auxiliary node becomes inactive
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	/** patrol point that we child actor facing at  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector PatrolPoint;

	/** time to wait at this patrol point  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector WaitTime;

};