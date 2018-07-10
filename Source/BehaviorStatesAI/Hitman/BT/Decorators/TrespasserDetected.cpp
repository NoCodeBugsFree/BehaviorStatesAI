// Fill out your copyright notice in the Description page of Project Settings.

#include "TrespasserDetected.h"
#include "Hitman/AIC.h"
#include "Hitman/Hitman.h"
#include "BehaviorTree/BlackboardComponent.h"

UTrespasserDetected::UTrespasserDetected()
{
	PreviousLocation.SelectedKeyName = "PreviousLocation";
	Target.SelectedKeyName = "Target";
	Trespasser.SelectedKeyName = "Trespasser";

	NodeName = FString("Trespasser Detected");
	FlowAbortMode = EBTFlowAbortMode::None;
	SetIsInversed(false);

	bNotifyActivation = true;
	bNotifyDeactivation = true;
}

bool UTrespasserDetected::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return true;
}

void UTrespasserDetected::OnNodeActivation(FBehaviorTreeSearchData& SearchData)
{
	if(AAIC* TestAIC = Cast<AAIC>(SearchData.OwnerComp.GetAIOwner()))
	{
		/** cache the AIC reference  */
		AIC = TestAIC;

		APawn* AIP = AIC->GetPawn();

		UBlackboardComponent* BB = SearchData.OwnerComp.GetBlackboardComponent();

		if (AIP && BB)
		{
			/** save last AI location to blackboard  */
			BB->SetValueAsVector(PreviousLocation.SelectedKeyName, AIP->GetActorLocation());

			/** start attack Hitman by timer  */
			AIC->StartAttack(true, TimeBeforeAttack);

			/** save potential target to blackboard  */
			UObject* PotentialTarget = BB->GetValueAsObject(Trespasser.SelectedKeyName);
			if (PotentialTarget)
			{
				BB->SetValueAsObject(Target.SelectedKeyName, PotentialTarget);
			}
		}
	}
}

void UTrespasserDetected::OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult)
{
	UBlackboardComponent* BB = SearchData.OwnerComp.GetBlackboardComponent();
	if (BB)
	{
		/** clear previous location  */
		BB->ClearValue(PreviousLocation.SelectedKeyName);

		/** if Hitman left forbidden area disable attack timer  */
		UObject* PotentialHitman = BB->GetValueAsObject(Target.SelectedKeyName);
		if(AHitman* Hitman = Cast<AHitman>(PotentialHitman))
		{
			if ( ! Hitman->IsTrespasser() )
			{
				if (AIC)
				{
					AIC->StartAttack(false);
				}
			}
		}
		/** clear potential target  */
		BB->ClearValue(Target.SelectedKeyName);
	}
}
