// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Hitman.generated.h"

UCLASS()
class BEHAVIORSTATESAI_API AHitman : public ABaseCharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/* sphere collision  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* InteractionSphere;

public:

	AHitman();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	
	virtual void BeginPlay() override;

	virtual void Landed(const FHitResult& Hit);

	/** BlueprintNativeEvent fired when the character has just started jumping */
	virtual void OnJumped_Implementation() override;

	virtual void PostInitializeComponents() override;

private:

	/* calls when interaction sphere overlaps by other actor */
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	/** called for forwards/backward input */
	void MoveForward(float Value);

	/** called for side to side input */
	void MoveRight(float Value);

	/** flipflop Walk and Jog  */
	void ToggleJog();

	/** flipflop Walk and Sprint  */
	void ToggleSprint();

	/** flipflop Walk and Crouch  */
	void ToggleCrouch();

	/** called to make some noise if we move to fast */
	void MakeMovementNoise();
	// -----------------------------------------------------------------------------------
	
public:	
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	/** retunrs current transform of the left arm socket **/
	//FORCEINLINE FTransform GetLeftArmSocketTransform() const { return CurrentWeapon ? CurrentWeapon->GetLeftArmSocketTransform() : FTransform(); }
};
