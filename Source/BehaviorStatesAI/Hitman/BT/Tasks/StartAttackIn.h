// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "StartAttackIn.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORSTATESAI_API UStartAttackIn : public UBTTaskNode
{
	GENERATED_BODY()
	
private:

	UStartAttackIn();
	
	/** starts this task, should return Succeeded, Failed or InProgress
	*  (use FinishLatentTask() when returning InProgress)
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	uint32 bShouldStart : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float TimeToAttackHitman = 15.f;

};
