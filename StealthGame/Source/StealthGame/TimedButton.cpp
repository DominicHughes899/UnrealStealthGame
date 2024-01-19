// Fill out your copyright notice in the Description page of Project Settings.


#include "TimedButton.h"

void ATimedButton::InteractChild(ACharacter* Character)
{

	if (!IsPressed)
	{
		IsPressed = true;

		OnPressed();

		
		if (LinkedInteractee)
		{
			LinkedInteractee->Execute_ButtonStateChange(LinkedActor, IsPressed);
		}
	}
}

void ATimedButton::OnBeginPlay()
{
	LinkedInteractee = Cast<IInteractInterface>(LinkedActor);
	if (LinkedInteractee == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("LINKED ACTOR CAST FAILED"));
	}

}

void ATimedButton::OnTick(float DeltaTime)
{
	if (IsPressed)
	{
		Timer -= DeltaTime;

		if (Timer <= Counter)
		{
			OnCounterChanged(Counter);
			Counter--;
		}

		if (Timer <= 0)
		{
			IsPressed = false;

			Counter = ActivationPeriod;
			Timer = ActivationPeriod;

			OnTimeout();

			// Interaface
			if (LinkedInteractee)
			{
				LinkedInteractee->Execute_ButtonStateChange(LinkedActor, IsPressed);
			}
		}
	}
}