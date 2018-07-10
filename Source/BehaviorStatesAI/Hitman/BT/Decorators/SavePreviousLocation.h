// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SavePreviousLocation.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORSTATESAI_API USavePreviousLocation : public UBTDecorator
{
	GENERATED_BODY()
	
private:

	USavePreviousLocation();
	
	/** Target To Follow  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector PreviousLocation;

	/** calculates raw, core value of decorator's condition. Should not include calling IsInversed */
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	/** called when underlying node is activated
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;

	/** called when underlying node has finished
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult) override;
};
