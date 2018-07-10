// Fill out your copyright notice in the Description page of Project Settings.

#include "FacingTo.h"
#include "Hitman/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Hitman/AIC.h"

UFacingTo::UFacingTo()
{
	Target.SelectedKeyName = "Target";
	NodeName = FString("Facing To");
	Interval = 0.5f;
	RandomDeviation = 0.1f;
	bCallTickOnSearchStart = true;

	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}

void UFacingTo::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIC* AIC = Cast<AAIC>(OwnerComp.GetAIOwner()))
	{
		if (ABaseCharacter* AIP = Cast<ABaseCharacter>(AIC->GetPawn()))
		{
			/** allow AIC rotate the pawn  */
			AIP->GetCharacterMovement()->bOrientRotationToMovement = false;
			if (ABaseCharacter* TargetCharacter = Cast<ABaseCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Target.SelectedKeyName)))
			{
				/** focus to Hitman  */
				AIC->SetFocus(TargetCharacter);
			}
		}
	}
}

void UFacingTo::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
