// Fill out your copyright notice in the Description page of Project Settings.

#include "TellAboutCrime.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Hitman/BaseCharacter.h"
#include "Hitman/AIC.h"

UTellAboutCrime::UTellAboutCrime()
{
	LastCrimeLocation.SelectedKeyName = "LastCrimeLocation";
	LastHitmanLocation.SelectedKeyName = "LastHitmanLocation";
	SawCrime.SelectedKeyName = "SawCrime";

	NodeName = FString("Tell About Crime");
	Interval = 1.f;
	RandomDeviation = 0.1f;
	bCallTickOnSearchStart = false;
}

void UTellAboutCrime::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UAIPerceptionComponent* AIPerceptionComponent = Cast<UAIPerceptionComponent>(OwnerComp.GetAIOwner()->GetComponentByClass(UAIPerceptionComponent::StaticClass()));
	if (AIPerceptionComponent)
	{
		TArray<AActor*> OutActors;
		AIPerceptionComponent->GetKnownPerceivedActors(UAISense_Sight::StaticClass(), OutActors);

		/** for each known actor set crime data  */
		for (AActor* TestActor : OutActors)
		{
			if (ABaseCharacter* AIP = Cast<ABaseCharacter>(TestActor))
			{
				AAIC* AIC = AIP->GetAIC();
				if (AIC)
				{
					/** get crime data from our blackboard  */
					FVector CrimeLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(LastCrimeLocation.SelectedKeyName);
					FVector HitmanLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(LastHitmanLocation.SelectedKeyName);
					bool bSawCrime = OwnerComp.GetBlackboardComponent()->GetValueAsBool(SawCrime.SelectedKeyName);

					/** and send it to other AIC blackboard  */
					AIC->GetBlackboardComp()->SetValueAsVector(LastCrimeLocation.SelectedKeyName, CrimeLocation);
					AIC->GetBlackboardComp()->SetValueAsVector(LastHitmanLocation.SelectedKeyName, HitmanLocation);
					AIC->GetBlackboardComp()->SetValueAsBool(SawCrime.SelectedKeyName, bSawCrime);

					/** set corresponding AI state  */
					AIC->SetAIState(AIC->OnDetectCrimeState);
				}
			}
		}
	}
}
