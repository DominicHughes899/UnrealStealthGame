// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable_Lever.h"


void AInteractable_Lever::InteractChild(ACharacter* Character)
{
	LeverState = !LeverState;

	LeverInteraction();

	if (LinkedInteractee)
	{
		LinkedInteractee->Execute_LeverStateChange(LinkedActor, LeverState);
	}
}

void AInteractable_Lever::OnBeginPlay()
{
	LinkedInteractee = Cast<IInteractInterface>(LinkedActor);

	if (LinkedInteractee == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("LINKED ACTOR CAST FAILED"));
	}
}
