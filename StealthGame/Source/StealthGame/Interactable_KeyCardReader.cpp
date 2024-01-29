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

			if (LinkedLockedInteractee)
			{
				LinkedLockedInteractee->Execute_Unlock(LinkedLockedActor);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("UNLOCK FAILED"));
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

	LinkedLockedInteractee = Cast<ILockInterface>(LinkedLockedActor);
	if (LinkedLockedInteractee == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("KEYCARD LOCKED ACTOR CAST FAILED"));
	}

}
