// Fill out your copyright notice in the Description page of Project Settings.

#include "StartAttackIn.h"
#include "Hitman/AIC.h"

UStartAttackIn::UStartAttackIn()
{
	NodeName = FString("Start Attack In");
}

EBTNodeResult::Type UStartAttackIn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(AAIC* AIC = Cast<AAIC>(OwnerComp.GetAIOwner()))
	{
		AIC->StartAttack(bShouldStart, TimeToAttackHitman);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
