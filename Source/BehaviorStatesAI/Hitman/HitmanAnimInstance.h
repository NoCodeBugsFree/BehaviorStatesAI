// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HitmanAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIORSTATESAI_API UHitmanAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:

	/** current character's aim pitch  */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float AimPitch;

	/** current character's speed  */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float Speed;

	/** current character's movement direction  */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	float Direction;

	/** shows whether character is jumping or not  */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	uint32 bJump : 1;

	/** shows whether character is dead or not  */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	uint32 bDead : 1;

	/** shows whether character is crouching or not  */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	uint32 bCrouch : 1;

	/** shows whether character is armed or not */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	uint32 bArmed : 1;

	/** the point in the 3D-space to attach the player's left arm when we are aiming  */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	FTransform LeftHandTransform;

	/** owning pawn reference  */
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	class ABaseCharacter* BaseCharacter;
	
	
};
