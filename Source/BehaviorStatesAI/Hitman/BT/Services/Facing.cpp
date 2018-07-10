// Fill out your copyright notice in the Description page of Project Settings.

#include "Facing.h"
#include "Hitman/BaseCharacter.h"
#include "Hitman/AIC.h"
#include "Hitman/PatrolPath.h"
#include "Hitman/PatrolPoint.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UFacing::UFacing()
{
	PatrolPoint.SelectedKeyName = "PatrolPoint";
	WaitTime.SelectedKeyName = "WaitTime";
	NodeName = FString("Facing");
	Interval = 0.5f;
	RandomDeviation = 0.1f;
	bCallTickOnSearchStart = true;

	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

void UFacing::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIC* AIC = Cast<AAIC>(OwnerComp.GetAIOwner()))
	{
		if (ABaseCharacter* AIP = Cast<ABaseCharacter>(AIC->GetPawn()))
		{
			/** allow AIC rotate the pawn  */
			AIP->GetCharacterMovement()->bOrientRotationToMovement = false;
			if(APatrolPoint* PP = Cast<APatrolPoint>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(PatrolPoint.SelectedKeyName)))
			{
				/** if patrol point is valid and child actor (actor to focus is valid)  */
				if (PP->GetFacingTarget() && PP->GetFacingTarget()->GetChildActor())
				{
					/** and we should facing  */
					if (PP->UseFacing())
					{
						AIC->SetFocus(PP->GetFacingTarget()->GetChildActor());
					}
				}

				/** set wait time to blackboard  */
				OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitTime.SelectedKeyName, PP->GetRandomWaitTime());
			}
		}
	}
}

void UFacing::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIC* AIC = Cast<AAIC>(OwnerComp.GetAIOwner()))
	{
		if (ABaseCharacter* AIP = Cast<ABaseCharacter>(AIC->GetPawn()))
		{
			/** rotate pawn to movement  */
			AIP->GetCharacterMovement()->bOrientRotationToMovement = true;
			AIC->ClearFocus(EAIFocusPriority::Gameplay);
		}
	}
}
