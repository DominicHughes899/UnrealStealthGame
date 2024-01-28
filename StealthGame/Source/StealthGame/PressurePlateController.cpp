// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlateController.h"

// Sets default values
APressurePlateController::APressurePlateController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APressurePlateController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APressurePlateController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APressurePlateController::CheckCodeInput(int Value)
{
	if (!HasActivated)
	{

		if (Value == DesiredSequence[Counter])
		{
			Counter++;

			if (Counter == DesiredSequence.Num())
			{
				Counter = 0;
				OnCodeCorrect();

				HasActivated = true;
			}
		}
		else
		{
			Counter = 0;
			OnCodeIncorrect();
		}
	}

}

