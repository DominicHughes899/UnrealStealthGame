// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"

#include "InteractInterface.h"

#include "Interactable_Lever.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHGAME_API AInteractable_Lever : public AInteractable
{
	GENERATED_BODY()
	
public: 

	void InteractChild(ACharacter* Character) override;

	void OnBeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void LeverInteraction();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool LeverState = false;

};
