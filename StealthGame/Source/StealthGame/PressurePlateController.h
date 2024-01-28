// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PressurePlateInterface.h"

#include "PressurePlateController.generated.h"

UCLASS()
class STEALTHGAME_API APressurePlateController : public AActor, public IPressurePlateInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePlateController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TArray<int> DesiredSequence;

	int Counter = 0;

	void CheckCodeInput(int Value);

	bool HasActivated = false;

	// Interface function
	void CodeInput_Implementation(int value) override { CheckCodeInput(value); }


	// Blueprint Functions
	UFUNCTION(BlueprintImplementableEvent)
	void OnCodeIncorrect();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCodeCorrect();



};
