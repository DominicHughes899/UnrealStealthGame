// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable_KeyCardReader.h"
#include "GameFramework/Character.h"
#include "StealthGameCharacter.h"

void AInteractable_KeyCardReader::InteractChild(ACharacter* Character)
{
	if (!Activated)
	{
		if (Character->ActorHasTag(AcceptedCard))
		{
			OnAccessGranted();

			Activated = true;

			if (LinkedInteractee)
			{
				LinkedInteractee->Execute_Unlock(LinkedActor);
			}

			AStealthGameCharacter* AsStealthCharacter = Cast<AStealthGameCharacter>(Character);

			AsStealthCharacter->ClearHeldItem();
		}
		else
		{
			OnAccessDenied();
		}
	}
	
}

void AInteractable_KeyCardReader::OnBeginPlay()
{

	LinkedInteractee = Cast<ILockInterface>(LinkedActor);
	if (LinkedInteractee == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("LINKED ACTOR CAST FAILED"));
	}

}
