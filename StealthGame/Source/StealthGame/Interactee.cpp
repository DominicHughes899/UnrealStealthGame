// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactee.h"

// Sets default values
AInteractee::AInteractee()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractee::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractee::LeverStateChange_Implementation(bool NewState)
{
	Activated = NewState;

	OnStateChange();
}

void AInteractee::ButtonStateChange_Implementation(bool NewState)
{
	Activated = NewState;

	OnStateChange();
}

void AInteractee::TimerStateChange_Implementation(bool NewState)
{
	Activated = NewState;

	OnStateChange();
}



