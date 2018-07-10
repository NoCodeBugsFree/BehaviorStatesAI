// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrolPath.h"
#include "PatrolPoint.h"
#include "Components/TextRenderComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/SplineComponent.h"

// Sets default values
APatrolPath::APatrolPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/* billboard  */
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	SetRootComponent(Billboard);

	/** spline component */
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(RootComponent);

	/** defaults  */
	bLooping = true;
	bWalking = true;
	bShowPatrol = true;
}
