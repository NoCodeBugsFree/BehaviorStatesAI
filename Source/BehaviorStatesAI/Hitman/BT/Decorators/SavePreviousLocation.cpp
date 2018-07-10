// Fill out your copyright notice in the Description page of Project Settings.

#include "SavePreviousLocation.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

USavePreviousLocation::USavePreviousLocation()
{
	PreviousLocation.SelectedKeyName = "PreviousLocation";
	NodeName = FString("Save Previous Location");
	FlowAbortMode = EBTFlowAbortMode::None;
	SetIsInversed(false);

	bNotifyActivation = true;
	bNotifyDeactivation = true;
}

bool USavePreviousLocation::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return true;
}

void USavePreviousLocation::OnNodeActivation(FBehaviorTreeSearchData& SearchData)
{
	UBlackboardComponent* BB = SearchData.OwnerComp.GetBlackboardComponent();
	if (BB)
	{
		if (SearchData.OwnerComp.GetAIOwner())
		{
			APawn* AIP = SearchData.OwnerComp.GetAIOwner()->GetPawn();
			if (AIP)
			{
				/** save our current location to further use  */
				BB->SetValueAsVector(PreviousLocation.SelectedKeyName, AIP->GetActorLocation());
			}
		}
	}
}

void USavePreviousLocation::OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult)
{
	UBlackboardComponent* BB = SearchData.OwnerComp.GetBlackboardComponent();
	if (BB)
	{
		/** erase cached location  */
		BB->ClearValue(PreviousLocation.SelectedKeyName);
	}
}
