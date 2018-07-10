// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SawCrime.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORSTATESAI_API USawCrime : public UBTDecorator
{
	GENERATED_BODY()
	
	private:

	USawCrime();
	
	/** Target To Follow  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector SawCrime;

	/** calculates raw, core value of decorator's condition. Should not include calling IsInversed */
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
