// Fill out your copyright notice in the Description page of Project Settings.


#include "ColourPressurePlateController.h"

// Sets default values
AColourPressurePlateController::AColourPressurePlateController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AColourPressurePlateController::BeginPlay()
{
	Super::BeginPlay();
	
	for (int Slot : DesiredColourSequence)
	{
		InputSequence.Add(0);
	}
}

// Called every frame
void AColourPressurePlateController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AColourPressurePlateController::CheckColourCodeInput(int Location, int Value)
{
	if (Location < InputSequence.Num())
	{
		InputSequence[Location] = Value; 

	}

	int Counter = 0;
	bool Success = true;

	for (int CorrectValue : DesiredColourSequence)
	{
		if (CorrectValue == InputSequence[Counter])
		{
			Counter++;
		}
		else
		{
			Success = false; 
			break;
		}
	}

	if (Success)
	{
		if (LinkedInteractee)
		{
			LinkedInteractee->Execute_ButtonStateChange(LinkedActor, true);
		}

		OnCodeCorrect();
	}
}