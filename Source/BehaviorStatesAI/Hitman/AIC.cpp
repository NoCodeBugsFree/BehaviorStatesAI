// Fill out your copyright notice in the Description page of Project Settings.

#include "AIC.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Hitman.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Hitman/BaseCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "ConstructorHelpers.h"
#include "DrawDebugHelpers.h"

AAIC::AAIC()
{
	/** AI Perception Component  */
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	/** sight sense config template to our AI  */
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	Sight->SightRadius = 2000.f;
	Sight->LoseSightRadius = 2500.f;
	Sight->PeripheralVisionAngleDegrees = 60.f;
	Sight->SetMaxAge(10.f);
	Sight->AutoSuccessRangeFromLastSeenLocation = -1.f;

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerceptionComponent->ConfigureSense(*Sight);

	/** hearing sense config template to our AI  */
	Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	Hearing->HearingRange = 3000.f;
	Hearing->DetectionByAffiliation.bDetectEnemies = true;
	Hearing->DetectionByAffiliation.bDetectFriendlies = true;
	Hearing->DetectionByAffiliation.bDetectNeutrals = true;
	Hearing->SetMaxAge(10.f);

	AIPerceptionComponent->ConfigureSense(*Hearing);
	AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());

	/** Blackboard Component  */
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	/** BehaviorTree Component  */
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));

	/** class defaults  */
	bAttachToPawn = true;
}

void AAIC::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	if(ABaseCharacter* AIP = Cast<ABaseCharacter>(Pawn))
	{
		/** cache the pawn reference  */
		AIPawn = AIP;

		// Initialize Blackboard and Start Behavior Tree
		if (Pawn && BehaviorTree && BehaviorTree->BlackboardAsset)
		{
			BlackboardComponent->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
			BehaviorTreeComponent->StartTree(*BehaviorTree);
		}
		
		/** init AIState  */
		SetAIState(AIP->AIState);

		/** init on detect crime state  */
		OnDetectCrimeState = AIP->OnDetectCrimeState;
	}
}

void AAIC::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AAIC::OnPerceptionUpdated);
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAIC::OnTargetPerceptionUpdated);
}

void AAIC::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* Actor : UpdatedActors)
	{
		FActorPerceptionBlueprintInfo Info;
		if (AIPerceptionComponent->GetActorsPerception(Actor, Info))
		{
			/** Index is number (in the Senses Config array) of sense config element, for instance 
			*	Index == 0 is our SightConfig
			*	Index == 1 is our HearingConfig
			*/

			int32 Index = 0;
			for (FAIStimulus& AIStimulus : Info.LastSensedStimuli)
			{
				if (AIStimulus.IsActive())
				{
					switch (Index)
					{
						/** Sight Config  */
						case 0:
							// UE_LOG(LogTemp, Error, TEXT("I saw %s at location %s"), *Actor->GetName(), *AIStimulus.StimulusLocation.ToString());
							// DrawDebugSphere(GetWorld(), AIStimulus.StimulusLocation, 100.f, 12, FColor::Green, false, 5.f, 0, 1.f);
							break;
						
						/** Hearing Config  */
						case 1:
							// UE_LOG(LogTemp, Error, TEXT("I heard %s at location %s"), *Actor->GetName(), *AIStimulus.StimulusLocation.ToString());
							// DrawDebugSphere(GetWorld(), AIStimulus.StimulusLocation, 100.f, 12, FColor::Blue, false, 5.f, 0, 1.f);
							break;
					
						default:
							break;
					}
				}
				Index++;
			}
		}
	}
}

void AAIC::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	TSubclassOf<UAISense> TempSens = UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus);
	if (TempSens == UAISense_Sight::StaticClass())
	{
		UE_LOG(LogTemp, Error, TEXT("I saw %s at location : %s"), *Actor->GetName(), *Stimulus.StimulusLocation.ToString());
		DrawDebugSphere(GetWorld(), Stimulus.StimulusLocation, 100.f, 12, FColor::Green, false, 5.f, 0, 1.f);
	}
	else if (TempSens == UAISense_Hearing::StaticClass())
	{
		UE_LOG(LogTemp, Error, TEXT("I heard %s at location : %s"), *Actor->GetName(), *Stimulus.StimulusLocation.ToString());
		DrawDebugSphere(GetWorld(), Stimulus.StimulusLocation, 100.f, 12, FColor::Blue, false, 5.f, 0, 1.f);

		/** simple ignore noise when we are hostile */
		if (HitmanAIState != EHitmanAIState::HAS_Hostile)
		{
			/** we are vigilant (SC unit quotation)  */
			SetAIState(EHitmanAIState::HAS_Vigilant);
			BlackboardComponent->SetValueAsVector(FName(TEXT("LocationToGo")), Stimulus.StimulusLocation);
		}
	}
}

void AAIC::SetAIState_Implementation(EHitmanAIState NewState)
{
	if (NewState != HitmanAIState)
	{
		/** update state here  */
		HitmanAIState = NewState;

		/** update blackboard value  */
		BlackboardComponent->SetValueAsEnum("AIState", (uint8)HitmanAIState);

		/** adjust color and speed in BP  */
	}
}

void AAIC::StartAttack(bool bShouldStart, float TimeToStartAttackHitman /*= 15.f*/)
{
	if (bShouldStart)
	{
		GetWorldTimerManager().SetTimer(AttackHitmanTimer, this, &AAIC::SetSawCrime, TimeToStartAttackHitman, false);
	} 
	else
	{
		GetWorldTimerManager().ClearTimer(AttackHitmanTimer);
	}
}

void AAIC::SetSawCrime()
{
	BlackboardComponent->SetValueAsBool(FName(TEXT("SawCrime")), true);
}
