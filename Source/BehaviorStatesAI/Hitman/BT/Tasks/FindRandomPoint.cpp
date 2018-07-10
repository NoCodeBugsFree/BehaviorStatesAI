// Fill out your copyright notice in the Description page of Project Settings.

#include "FindRandomPoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Navigation/NavigationSystem.h"

UFindRandomPoint::UFindRandomPoint()
{
	LocationToGo.SelectedKeyName = "LocationToGo";
	NodeName = FString("Find Random Point");
}

EBTNodeResult::Type UFindRandomPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (OwnerComp.GetAIOwner())
	{
		APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
		if (AIPawn)
		{
			UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
			if (BB)
			{
				/** get random point in radius at AI Pawn location  */
				if (GetWorld()->GetNavigationSystem())
				{
					FNavLocation RandomPoint;
					if (GetWorld()->GetNavigationSystem()->GetRandomReachablePointInRadius(AIPawn->GetActorLocation(),
						FMath::RandRange(MinRadius, MaxRadius), RandomPoint))
					{
						BB->SetValueAsVector(LocationToGo.SelectedKeyName, RandomPoint.Location);
						return EBTNodeResult::Succeeded;
					}
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
