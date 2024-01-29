// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LockInterface.h"
#include "InteractInterface.h"

#include "Interactable.generated.h"

UCLASS()
class STEALTHGAME_API AInteractable : public AActor, public ILockInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact(ACharacter* Character);

	virtual void InteractChild(ACharacter* Character) {}

	
	virtual void OnBeginPlay() {}
	virtual void OnTick(float DeltaTime) {}


	// ==== Lock Implementation ====

	void Unlock_Implementation() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnLocked();

	UPROPERTY(EditAnywhere, Category = "Interactable")
	bool Locked = false;

	// ==== Interactable ====

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AActor* LinkedActor;

	IInteractInterface* LinkedInteractee;


};
