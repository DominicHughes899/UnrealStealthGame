// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"

// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &APressurePlate::PressurePlateTriggered);
	OnActorEndOverlap.AddDynamic(this, &APressurePlate::PressurePlateUnTriggered);

	// Link Interface
	LinkedInterface = Cast<IPressurePlateInterface>(LinkedController);
	if (!LinkedInterface)
	{
		UE_LOG(LogTemp, Error, TEXT("Linked pressure plate controller cast FAILED!"));
	}
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APressurePlate::PressurePlateTriggered(class AActor* OverlappedActor, class AActor* OtherActor)
{
	SetActorTickEnabled(true);

	IsPlatePressed = true;

	LinkedInterface->Execute_CodeInput(LinkedController, CodeValue);

	OnPressurePlateTriggered();
}

void APressurePlate::PressurePlateUnTriggered(AActor* OverlappedActor, AActor* OtherActor)
{
	SetActorTickEnabled(true);

	IsPlatePressed = false;

}

