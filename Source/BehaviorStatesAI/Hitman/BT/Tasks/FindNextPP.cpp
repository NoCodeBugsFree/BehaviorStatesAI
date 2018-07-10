// Fill out your copyright notice in the Description page of Project Settings.

#include "FindNextPP.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Hitman/BaseCharacter.h"
#include "Hitman/AIC.h"
#include "Hitman/PatrolPath.h"

UFindNextPP::UFindNextPP()
{
	PatrolPoint.SelectedKeyName = "PatrolPoint";
	NodeName = FString("Find Next Patrol Point");
}

EBTNodeResult::Type UFindNextPP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(AAIC* AIC = Cast<AAIC>(OwnerComp.GetAIOwner()))
	{
		if(ABaseCharacter* AIP = Cast<ABaseCharacter>(AIC->GetPawn()))
		{
			/** get a patrol path from pawn and set next patrol point to the blackboard */
			APatrolPath* PatrolPath = AIP->GetPatrolPath();
			if (PatrolPath)
			{
				if (PatrolPath->GetPatrolPoints().IsValidIndex(Index))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(PatrolPoint.SelectedKeyName, (UObject*)PatrolPath->GetPatrolPoints()[Index]);
					Index++;
					if (Index >= PatrolPath->GetPatrolPoints().Num())
					{
						Index = 0;
					}
					return EBTNodeResult::Succeeded;
				}
			} 
			else /** we haven't patrol path - start wandering  */
			{
				UE_LOG(LogTemp, Warning, TEXT("No patrol path ... Starts wandering. . ."));
				AIC->SetAIState(EHitmanAIState::HAS_Wander);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
