// Fill out your copyright notice in the Description page of Project Settings.

#include "Fire.h"
#include "AIController.h"
#include "Hitman/BaseCharacter.h"

UFire::UFire()
{
	NodeName = FString("F i r e");
}

EBTNodeResult::Type UFire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (OwnerComp.GetAIOwner())
	{
		if(ABaseCharacter* AIP = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
		{
			AIP->Fire();
		}
	}
	return EBTNodeResult::Succeeded;
}
