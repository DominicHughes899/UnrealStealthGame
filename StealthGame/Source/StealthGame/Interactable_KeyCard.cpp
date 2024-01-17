// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable_KeyCard.h"
#include "StealthGameCharacter.h"

void AInteractable_KeyCard::InteractChild(ACharacter* Character)
{
	if (!Collected)
	{
		UE_LOG(LogTemp, Warning, TEXT("Keycard Activated"));

		AStealthGameCharacter* AsStealthCharacter = Cast<AStealthGameCharacter>(Character);

		if (AsStealthCharacter)
		{
			if (AsStealthCharacter->AttachHeldItem(this, Tag))
			{
				OnInteracted(true);
				Collected = true;
			}

			else { OnInteracted(false); }
		}
	}


}