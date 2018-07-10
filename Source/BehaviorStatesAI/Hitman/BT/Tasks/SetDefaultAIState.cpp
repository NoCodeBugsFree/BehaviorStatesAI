// Fill out your copyright notice in the Description page of Project Settings.

#include "SetDefaultAIState.h"
#include "Hitman/BaseCharacter.h"
#include "Hitman/AIC.h"
#include "BehaviorTree/BlackboardComponent.h"

USetDefaultAIState::USetDefaultAIState()
{
	NodeName = FString("Set Initial AI State");
}

EBTNodeResult::Type USetDefaultAIState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(AAIC* AIC = Cast<AAIC>(OwnerComp.GetAIOwner()))
	{
		if(ABaseCharacter* AIP = Cast<ABaseCharacter>(AIC->GetPawn()))
		{
			UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
			if (BB)
			{
				/** set the initial AI state  */
				AIC->SetAIState(AIP->InitialAIState);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
