// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable_Lever.h"


void AInteractable_Lever::InteractChild(ACharacter* Character)
{
	LeverState = !LeverState;

	LeverInteraction();

	ILeverInterface* Interface = Cast<ILeverInterface>(LinkedActor);

	if (Interface)
	{
		UE_LOG(LogTemp, Warning, TEXT("InterfaceCalled"));

		Interface->Execute_LeverUpdate(LinkedActor, LeverState);
	}
}
