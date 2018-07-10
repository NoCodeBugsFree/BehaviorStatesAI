// Fill out your copyright notice in the Description page of Project Settings.

#include "HitmanAnimInstance.h"
#include "BaseCharacter.h"

void UHitmanAnimInstance::NativeInitializeAnimation()
{
	if (ABaseCharacter* TestBaseCharacter = Cast<ABaseCharacter>(TryGetPawnOwner()))
	{
		BaseCharacter = TestBaseCharacter;
	}
}

void UHitmanAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (BaseCharacter)
	{
		FVector CharacterVelocity = BaseCharacter->GetVelocity();
		FRotator CharacterRotation = BaseCharacter->GetActorRotation();

		/** speed  */
		Speed = CharacterVelocity.Size();

		/** direction  */
		Direction = CalculateDirection(CharacterVelocity, CharacterRotation);

		/** crouch  */
		bCrouch = BaseCharacter->bIsCrouched;

		/** jumping  */
		bJump = BaseCharacter->IsJumpedLastFrame();

		/** dead  */
		bDead = BaseCharacter->IsDead();

		/** dead  */
		bArmed = BaseCharacter->IsArmed();

		/** aim pitch  */
		AimPitch = BaseCharacter->GetAimPitch();
		
		/** left arm transform  */
		//LeftHandTransform = Hitman->GetLeftArmSocketTransform();
	}
}

