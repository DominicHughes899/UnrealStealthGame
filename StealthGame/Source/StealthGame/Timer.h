// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"

#include "InteractInterface.h"

#include "Timer.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHGAME_API ATimer : public AInteractable
{
	GENERATED_BODY()
	

public:
	virtual void OnBeginPlay() override;

	virtual void OnTick(float DeltaTime) override;

	float Timer = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	float OnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	float OffTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer")
	bool IsLightOn;



};
