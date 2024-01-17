// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Interactable_KeyCard.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHGAME_API AInteractable_KeyCard : public AInteractable
{
	GENERATED_BODY()
	
public:

	void InteractChild(ACharacter* Character) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteracted(bool Success);

	bool Collected = false;

	UPROPERTY(EditAnywhere)
	FName Tag;

};
