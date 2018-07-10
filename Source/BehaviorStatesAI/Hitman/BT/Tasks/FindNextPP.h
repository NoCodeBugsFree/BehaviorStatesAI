// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindNextPP.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORSTATESAI_API UFindNextPP : public UBTTaskNode
{
	GENERATED_BODY()
	
private:

	UFindNextPP();
	
	/** starts this task, should return Succeeded, Failed or InProgress
	*  (use FinishLatentTask() when returning InProgress)
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	// -----------------------------------------------------------------------------------

	/** Target To Follow Blackboard Key */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector PatrolPoint;
	
	/** patrol point index  */
	UPROPERTY()
	int32 Index = 0;
};
