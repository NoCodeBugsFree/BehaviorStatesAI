// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindRandomPoint.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORSTATESAI_API UFindRandomPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
private:

	UFindRandomPoint();

	/** starts this task, should return Succeeded, Failed or InProgress
	*  (use FinishLatentTask() when returning InProgress)
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	/** next location AI desire to go */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector LocationToGo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float MinRadius = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float MaxRadius = 5000.f;
};
