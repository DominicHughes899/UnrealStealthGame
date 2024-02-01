// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interactable.h"
#include "PressurePlateInterface.h"

#include "ColourPressurePlateController.generated.h"

UCLASS()
class STEALTHGAME_API AColourPressurePlateController : public AInteractable, public IPressurePlateInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColourPressurePlateController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TArray<int> DesiredColourSequence;

	TArray<int> InputSequence;

	// Interface Function

	void ColourCodeInput_Implementation(int Location, int value) override { CheckColourCodeInput(Location, value); }

	void CheckColourCodeInput(int Location, int Value);

	// Blueprint Functions

	UFUNCTION(BlueprintImplementableEvent)
	void OnCodeIncorrect();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCodeCorrect();


};

