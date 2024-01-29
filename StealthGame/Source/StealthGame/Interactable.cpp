// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
	LinkedInteractee = Cast<IInteractInterface>(LinkedActor);
	if (LinkedInteractee == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("LINKED ACTOR CAST FAILED"));
	}

	OnBeginPlay();
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OnTick(DeltaTime);
}

void AInteractable::Interact(ACharacter* Character)
{
	if (!Locked)
	{
		InteractChild(Character);
	}
	else
	{
		OnLocked();
	}
}

void AInteractable::Unlock_Implementation()
{
	Locked = false;
}

