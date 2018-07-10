// Fill out your copyright notice in the Description page of Project Settings.

#include "SawCrime.h"
#include "BehaviorTree/BlackboardComponent.h"

USawCrime::USawCrime()
{
	SawCrime.SelectedKeyName = "SawCrime";
	NodeName = FString("Saw Crime");
	FlowAbortMode = EBTFlowAbortMode::Self;
	SetIsInversed(true);
}

bool USawCrime::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (BB)
	{
		return BB->GetValueAsBool(SawCrime.SelectedKeyName);
	}
	return false;
}
