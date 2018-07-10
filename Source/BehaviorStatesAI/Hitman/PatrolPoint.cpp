// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrolPoint.h"
#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/ChildActorComponent.h"
#include "Engine/TargetPoint.h"

// Sets default values
APatrolPoint::APatrolPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/* scene component  */
	ROOT = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	SetRootComponent(ROOT);
	
	/* arrow component  */
	FocusDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("FocusDirection"));
	FocusDirection->SetupAttachment(RootComponent);
	FocusDirection->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	FocusDirection->ArrowSize = 3.f;
	FocusDirection->bHiddenInGame = false;
	
	/* billboard  */
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	Billboard->SetupAttachment(FocusDirection);
	Billboard->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));

	FacingTarget = CreateDefaultSubobject<UChildActorComponent>(TEXT("ChildActor"));
	FacingTarget->SetupAttachment(FocusDirection);
	FacingTarget->SetChildActorClass(ATargetPoint::StaticClass());
	FacingTarget->SetRelativeLocation(FVector(230.f, 0.f, 0.f));

	/* defaults  */
	bUseFacing = true;
}

float APatrolPoint::GetRandomWaitTime() const
{
	return FMath::RandRange(WaitTimeMin, WaitTimeMax);
}

