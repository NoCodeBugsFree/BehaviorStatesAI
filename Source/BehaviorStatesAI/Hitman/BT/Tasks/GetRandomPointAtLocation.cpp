// Fill out your copyright notice in the Description page of Project Settings.

#include "GetRandomPointAtLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Navigation/NavigationSystem.h"

UGetRandomPointAtLocation::UGetRandomPointAtLocation()
{
	RandomLocation.SelectedKeyName = "RandomLocation";
	LocationToGo.SelectedKeyName = "LocationToGo";
	NodeName = FString("Get Random Point At Location");
}

EBTNodeResult::Type UGetRandomPointAtLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (BB)
	{
		/** get noise location from blackboard  */
		FVector LocationToGoFromBB = BB->GetValueAsVector(LocationToGo.SelectedKeyName);

		/** find random point in radius to investigate  */
		if (GetWorld()->GetNavigationSystem())
		{
			FNavLocation RandomPoint;
			if (GetWorld()->GetNavigationSystem()->GetRandomReachablePointInRadius(LocationToGoFromBB,
				FMath::RandRange(MinRadius, MaxRadius), RandomPoint))
			{
				BB->SetValueAsVector(RandomLocation.SelectedKeyName, RandomPoint.Location);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
