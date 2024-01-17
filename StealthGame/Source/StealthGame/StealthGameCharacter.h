// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StealthGameCharacter.generated.h"

UCLASS(Blueprintable)
class AStealthGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AStealthGameCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Boom for items being held */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HeldItem, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* HeldItemBoom;

public:
	bool AttachHeldItem(AActor* ItemToAttach, FName Tag);

	void ClearHeldItem();
	
	AActor* HeldItem;



};

