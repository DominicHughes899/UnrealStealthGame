// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Interactable_KeyCardReader.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHGAME_API AInteractable_KeyCardReader : public AInteractable
{
	GENERATED_BODY()
	
public:
	void InteractChild(ACharacter* Character) override;

	UPROPERTY(EditAnywhere)
	FName AcceptedCard;

	UFUNCTION(BlueprintImplementableEvent)
	void OnAccessGranted();

	UFUNCTION(BlueprintImplementableEvent)
	void OnAccessDenied();

	bool Activated = false;
};
