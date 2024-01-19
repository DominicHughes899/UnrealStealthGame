// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"

#include "InteractInterface.h"

#include "TimedButton.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHGAME_API ATimedButton : public AInteractable
{
	GENERATED_BODY()
	
public:

	void InteractChild(ACharacter* Character) override;

	// ==== Timer Functions ====
	void OnBeginPlay() override;
	void OnTick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	int ActivationPeriod = 3;

	int Counter = ActivationPeriod;
	float Timer = ActivationPeriod;

	bool IsPressed = false;

	// ==== Blueprint Funcitons ====

	UFUNCTION(BlueprintImplementableEvent)
	void OnPressed();

	UFUNCTION(BlueprintImplementableEvent)
	void OnTimeout();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCounterChanged(int CounterNumber);
	// ==============================


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AActor* LinkedActor;

	IInteractInterface* LinkedInteractee;


};
