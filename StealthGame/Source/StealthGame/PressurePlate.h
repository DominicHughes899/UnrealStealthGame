// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PressurePlateController.h"
#include "PressurePlateInterface.h"

#include "PressurePlate.generated.h"

UCLASS()
class STEALTHGAME_API APressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePlate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void PressurePlateTriggered(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void PressurePlateUnTriggered(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void DisableTick() { SetActorTickEnabled(false); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CodeValue;

	UPROPERTY(BlueprintReadOnly)
	bool IsPlatePressed = false;

	UPROPERTY(EditAnywhere, Category="ColourPlate", meta = (ToolTip = "Only matters if this is a colour pressure plate"))
	int Location;

	// Linked Controller

	UPROPERTY(EditAnywhere)
	AActor* LinkedController;

	IPressurePlateInterface* LinkedInterface;

	// Blueprint functions
	UFUNCTION(BlueprintImplementableEvent)
	void OnPressurePlateTriggered();

	UPROPERTY(BlueprintReadWrite)
	bool IsColourPlate;

};
