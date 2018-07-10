// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TossItem.generated.h"

UCLASS()
class BEHAVIORSTATESAI_API ATossItem : public AActor
{
	GENERATED_BODY()

	/** static mesh component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TossItemMesh;
	
public:	
	
	ATossItem();

protected:

	/** owner  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	class AHitman* Hitman;
		
};
