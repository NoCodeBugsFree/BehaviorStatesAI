// Fill out your copyright notice in the Description page of Project Settings.

#include "FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Navigation/NavigationSystem.h"

UFindRandomLocation::UFindRandomLocation()
{
	LocationToGo.SelectedKeyName = "LocationToGo";
	NodeName = FString("Find Random Location");
	Interval = 5.0f;
	RandomDeviation = 1.f;
	bCallTickOnSearchStart = false;
}

void UFindRandomLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (BB)
	{
		FVector LastLocationToGo = BB->GetValueAsVector(LocationToGo.SelectedKeyName);
		
		if (GetWorld()->GetNavigationSystem())
		{
			FNavLocation RandomPoint;
			if (GetWorld()->GetNavigationSystem()->GetRandomReachablePointInRadius(LastLocationToGo, FMath::RandRange(Min, Max), RandomPoint))
			{
				BB->SetValueAsVector(LocationToGo.SelectedKeyName, RandomPoint.Location);
			}
		}
	}
}
