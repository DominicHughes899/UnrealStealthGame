// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interactee.h"
#include "InteractInterface.h"

#include "InteractSequencer.generated.h"

UCLASS()
class STEALTHGAME_API AInteractSequencer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractSequencer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ==== Interactees ====

	UPROPERTY(EditAnywhere)
	TArray<AInteractee*> InteracteesArray;

	TArray<IInteractInterface*> InterfaceArray;

	
	// ==== Sequencer ====

	int ArraySize;
	int Counter = 0;

	UPROPERTY(EditAnywhere)
	float SequenceTime;

	float Timer = 0;


	// ==== Pause ====

	bool CheckPause();

	UPROPERTY(EditAnywhere)
	TArray<int> PausePoints;

	int PauseCounter = 0;
	int PauseArraySize;
};
