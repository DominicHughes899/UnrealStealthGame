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

			AStealthGameCharacter* AsStealthCharacter = Cast<AStealthGameCharacter>(Character);

			AsStealthCharacter->ClearHeldItem();
		}
		else
		{
			OnAccessDenied();
		}
	}
	
}