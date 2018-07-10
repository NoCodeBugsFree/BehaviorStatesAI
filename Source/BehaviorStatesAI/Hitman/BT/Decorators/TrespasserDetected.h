// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "TrespasserDetected.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORSTATESAI_API UTrespasserDetected : public UBTDecorator
{
	GENERATED_BODY()
	
private:

	UTrespasserDetected();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector PreviousLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector Trespasser;
	
	/** time to become hostile to instigator  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float TimeBeforeAttack = 10.f;
	
	UPROPERTY(Transient)
	class AAIC* AIC;
	
	/** calculates raw, core value of decorator's condition. Should not include calling IsInversed */
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	/** called when underlying node is activated
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;
	
	/** called when underlying node has finished
	* this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult) override;
		
	
};
