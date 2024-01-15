// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LeverInterface.h"

#include "Door.generated.h"

UCLASS()
class STEALTHGAME_API ADoor : public AActor, public ILeverInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LeverUpdate_Implementation(bool NewState) override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdatePosition();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsOpen = false;

};
