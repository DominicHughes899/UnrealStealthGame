// Fill out your copyright notice in the Description page of Project Settings.


#include "Timer.h"

void ATimer::OnBeginPlay()
{
	LinkedInteractee = Cast<IInteractInterface>(LinkedActor);
	if (LinkedInteractee == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("LINKED ACTOR CAST FAILED"));
	}
}

void ATimer::OnTick(float DeltaTime)
{
	Timer += DeltaTime;

	if (IsLightOn)
	{
		if (Timer > OnTime)
		{
			IsLightOn = !IsLightOn;
			LinkedInteractee->Execute_TimerStateChange(LinkedActor, IsLightOn);

			UE_LOG(LogTemp, Warning, TEXT("Timer triggered"));
			Timer = 0.f;
		}
	}
	else if (!IsLightOn)
	{
		if (Timer > OffTime)
		{
			IsLightOn = !IsLightOn;
			LinkedInteractee->Execute_TimerStateChange(LinkedActor, IsLightOn);
			Timer = 0.f;
		}
	}
}
