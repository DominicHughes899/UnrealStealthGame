// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "InteractInterface.h"

#include "Interactee.generated.h"

UCLASS()
class STEALTHGAME_API AInteractee : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractee();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool Activated = false;


	// ==== Interface functions ====
	void LeverStateChange_Implementation(bool NewState) override;

	void ButtonStateChange_Implementation(bool NewState) override;

	void TimerStateChange_Implementation(bool NewState) override;


	/**/

	UFUNCTION(BlueprintImplementableEvent)
	void OnStateChange();

};
