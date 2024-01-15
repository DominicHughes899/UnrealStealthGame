// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable_Lever.h"


void AInteractable_Lever::InteractChild()
{
	LeverState = !LeverState;

	LeverInteraction();

	ILeverInterface* Interface = Cast<ILeverInterface>(LinkedActor);

	if (Interface)
	{
		Interface->Execute_LeverUpdate(LinkedActor, LeverState);
	}
}
