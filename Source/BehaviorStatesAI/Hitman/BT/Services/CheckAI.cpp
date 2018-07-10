// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckAI.h"
#include "Hitman/AIC.h"
#include "Hitman/BaseCharacter.h"
#include "Hitman/CrimeWasHere.h"
#include "Hitman/Hitman.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"

UCheckAI::UCheckAI()
{
	AIState.SelectedKeyName				= "AIState";
	LastCrimeLocation.SelectedKeyName	= "LastCrimeLocation";
	LastHitmanLocation.SelectedKeyName	= "LastHitmanLocation";
	Hitman.SelectedKeyName				= "Hitman";
	ArmedHitman.SelectedKeyName			= "ArmedHitman";
	SawCrime.SelectedKeyName			= "SawCrime";
	Trespasser.SelectedKeyName			= "Trespasser";

	NodeName							= FString("Check AI");
	Interval							= 1.5f;
	RandomDeviation						= 0.1f;
	bCallTickOnSearchStart				= false;
}

void UCheckAI::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	if (AAIC* AIC = Cast<AAIC>(OwnerComp.GetAIOwner()))
	{
		UAIPerceptionComponent* AIPerceptionComponent = AIC->GetAIPerceptionComponent();
		UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();

		if (AIPerceptionComponent && BB)
		{
			TArray<AActor*> OutActors;
			AIPerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), OutActors);

			for (AActor* TestActor : OutActors)
			{
				/** if we saw armed Hitman
				*	set crime data in AIC
				*	set Hitman and SawCrime blackboard keys
				*/
				if(AHitman* HitmanPawn = Cast<AHitman>(TestActor))
				{
					/** I am seeing Hitman with out weapon right now!  */
					BB->SetValueAsObject(Hitman.SelectedKeyName, HitmanPawn);
					CachedHitman = HitmanPawn;

					bool bTrespasser = HitmanPawn->IsTrespasser();
					if (bTrespasser)
					{
						BB->SetValueAsObject(Trespasser.SelectedKeyName, HitmanPawn);
						/** update AI state  */
						AIC->SetAIState(AIC->OnDetectCrimeState);
					}
					else
					{
						BB->ClearValue(Trespasser.SelectedKeyName);
					}
					
					bool bArmed = HitmanPawn->IsArmed();
					if (bArmed)
					{
						CacheArmedHitman = HitmanPawn;
	
						/** I am seeing armed Hitman right now!  */
						BB->SetValueAsObject(ArmedHitman.SelectedKeyName, HitmanPawn);

						/** set crime data to this AIC */
						FVector HitmanLocation = HitmanPawn->GetActorLocation();

						/** set data to blackboard  */
						AIC->GetBlackboardComp()->SetValueAsVector(LastCrimeLocation.SelectedKeyName, HitmanLocation);
						AIC->GetBlackboardComp()->SetValueAsVector(LastHitmanLocation.SelectedKeyName, HitmanLocation);

						/** we saw Armed Hitman  */
						BB->SetValueAsBool(SawCrime.SelectedKeyName, true);
						
						/** update AI state  */
						AIC->SetAIState(AIC->OnDetectCrimeState);
						
						/** Hitman was found, crime data is set,  get out of here */
						return;
					}
				}
			}

			/** if in all perceived actors we haven't a CachedHitman - clear Hitman blackboard value  */
			if (CachedHitman)
			{
				if (OutActors.Num() == 0 || OutActors.Find(CachedHitman) == INDEX_NONE)
				{
					BB->ClearValue(Hitman.SelectedKeyName);
				}
			}

			/** if in all perceived actors we haven't a CacheArmeddHitman - clear ArmeddHitman blackboard value  */
			if (CacheArmedHitman)
			{
				if (OutActors.Num() == 0 || OutActors.Find(CacheArmedHitman) == INDEX_NONE)
				{
					BB->ClearValue(ArmedHitman.SelectedKeyName);
				}
			}

			/** check for any dead character  */
			for (AActor* TestActor : OutActors)
			{
				if(ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(TestActor))
				{
					bool bDead = BaseCharacter->IsDead();
					if (bDead)
					{
						/**  set data to blackboard  */
						AIC->GetBlackboardComp()->SetValueAsVector(LastCrimeLocation.SelectedKeyName, BaseCharacter->GetActorLocation());

						/** update AI state  */
						AIC->SetAIState(AIC->OnDetectCrimeState);

						/** corpse found, get out of here  */
						return;
					}
				}
			}

			/** check for crime scene objects  */
			for (AActor* TestActor : OutActors)
			{
				if (ACrimeWasHere* CrimeWasHere = Cast<ACrimeWasHere>(TestActor))
				{
					/**  set data to blackboard  */
					AIC->GetBlackboardComp()->SetValueAsVector(LastCrimeLocation.SelectedKeyName, CrimeWasHere->GetActorLocation());

					/** update AI state  */
					AIC->SetAIState(AIC->OnDetectCrimeState);
				}
			}
		}
	}
}