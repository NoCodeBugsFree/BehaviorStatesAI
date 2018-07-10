// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPoint.generated.h"

UCLASS()
class BEHAVIORSTATESAI_API APatrolPoint : public AActor
{
	GENERATED_BODY()

	/* scene component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* ROOT;
	
	/* arrow component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* FocusDirection;
	
	/* billboard component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBillboardComponent* Billboard;
	
	/** a component that spawns an Actor when registered, and destroys it when unregistered.  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UChildActorComponent* FacingTarget;
	
public:	
	
	APatrolPoint();

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float WaitTimeMin = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float WaitTimeMax = 5.f;

	/** shows whether AI should facing to facing target or not  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	uint32 bUseFacing : 1;

public:
	/** retunts UseFacing or not **/
	FORCEINLINE bool UseFacing() const { return bUseFacing; }
	/** returns facing target child actor  **/
	FORCEINLINE class UChildActorComponent* GetFacingTarget() const { return FacingTarget; }
	/** returns random wait time on this patrol point  **/
	FORCEINLINE float GetRandomWaitTime() const;
};
