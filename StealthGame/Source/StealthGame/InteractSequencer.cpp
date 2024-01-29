// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractSequencer.h"

// Sets default values
AInteractSequencer::AInteractSequencer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractSequencer::BeginPlay()
{
	Super::BeginPlay();
	
	ArraySize = InteracteesArray.Num();

	for (AInteractee* Interactee : InteracteesArray)
	{
		IInteractInterface* InterfaceToAdd = Cast<IInteractInterface>(Interactee);

		if (InterfaceToAdd)
		{
			InterfaceArray.Add(InterfaceToAdd);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Sequencer Failed to add Interactee to Array!"));
		}
	}

	
}

// Called every frame
void AInteractSequencer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timer += DeltaTime;

	if (Timer >= SequenceTime)
	{
		Timer = 0;

		if (Counter == 0)
		{
			InterfaceArray[Counter]->Execute_ButtonStateChange(InteracteesArray[Counter], false);

			Counter++;
		}
		else if (Counter > 0 && Counter != ArraySize)
		{
			InterfaceArray[Counter - 1]->Execute_ButtonStateChange(InteracteesArray[Counter - 1], true);

			InterfaceArray[Counter]->Execute_ButtonStateChange(InteracteesArray[Counter], false);

			Counter++;
		}
		else if (Counter == ArraySize)
		{
			InterfaceArray[Counter - 1]->Execute_ButtonStateChange(InteracteesArray[Counter - 1], true);

			Counter = 0;
		}

	}
}

