// Fill out your copyright notice in the Description page of Project Settings.

#include "TossItem.h"
#include "ConstructorHelpers.h"

ATossItem::ATossItem()
{
	/** mesh  */
	TossItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TossItemMesh"));
	SetRootComponent(TossItemMesh);
	TossItemMesh->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	TossItemMesh->SetSimulatePhysics(true);

	/**  set the default static mesh */
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (Cube.Succeeded())
	{
		TossItemMesh->SetStaticMesh(Cube.Object);
	}
}


