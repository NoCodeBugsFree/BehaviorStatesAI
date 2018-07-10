// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPath.generated.h"

UCLASS()
class BEHAVIORSTATESAI_API APatrolPath : public AActor
{
	GENERATED_BODY()

	/* billboard component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBillboardComponent* Billboard;
	
	/** spline component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USplineComponent* Spline;
	
public:	
	
	APatrolPath();

private:
	
	/**   */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TArray<class APatrolPoint*> PatrolPoints;

	/**   */
	UPROPERTY(BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TArray<class UTextRenderComponent*> TextRenderComponents;

	/** shows whether is  or not  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	uint32 bLooping : 1;

	/** shows whether is  or not  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	uint32 bWalking : 1;

	/** shows whether is  or not  */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	uint32 bShowPatrol : 1;

public:

	/** returns patrol points **/
	FORCEINLINE TArray<class APatrolPoint*> GetPatrolPoints() const { return PatrolPoints; }
};
