// Copyright Epic Games, Inc. All Rights Reserved.

#include "StealthGamePlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "StealthGameCharacter.h"
#include "Engine/World.h"

#include "Interactable.h"
#include "Telescope.h"

AStealthGamePlayerController::AStealthGamePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AStealthGamePlayerController::BeginPlay()
{
	AssignControlledPawn();
}

void AStealthGamePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	TickMovement(DeltaTime);
}

void AStealthGamePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Point and click controls
	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AStealthGamePlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AStealthGamePlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("Interact", IE_Pressed, this, &AStealthGamePlayerController::OnInteractPressed);

	// WASD controls
	InputComponent->BindAxis("MoveForward", this, &AStealthGamePlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AStealthGamePlayerController::MoveRight);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AStealthGamePlayerController::OnTouchPressed);
	InputComponent->BindTouch(EInputEvent::IE_Released, this, &AStealthGamePlayerController::OnTouchReleased);

}

void AStealthGamePlayerController::TickMovement(float DeltaTime)
{
	if (bInputPressed)
	{
		FollowTime += DeltaTime;

		// Look for the touch location
		FVector HitLocation = FVector::ZeroVector;
		FHitResult Hit;
		if (bIsTouch)
		{
			GetHitResultUnderFinger(ETouchIndex::Touch1, ECC_Visibility, true, Hit);
		}
		else
		{
			GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		}
		HitLocation = Hit.Location;

		// Direct the Pawn towards that location
		APawn* const MyPawn = GetPawn();
		if (MyPawn)
		{
			FVector WorldDirection = (HitLocation - MyPawn->GetActorLocation()).GetSafeNormal();
			MyPawn->AddMovementInput(WorldDirection, 1.f, false);
		}
	}
	else
	{
		FollowTime = 0.f;
	}
}

void AStealthGamePlayerController::OnSetDestinationPressed()
{
	// We flag that the input is being pressed
	bInputPressed = true;
	// Just in case the character was moving because of a previous short press we stop it
	StopMovement();
}

void AStealthGamePlayerController::OnSetDestinationReleased()
{
	// Player is no longer pressing the input
	bInputPressed = false;

	// If it was a short press
	if(FollowTime <= ShortPressThreshold)
	{
		// We look for the location in the world where the player has pressed the input
		FVector HitLocation = FVector::ZeroVector;
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		HitLocation = Hit.Location;

		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, HitLocation);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, HitLocation, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}
}

void AStealthGamePlayerController::OnTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	bIsTouch = true;
	OnSetDestinationPressed();
}

void AStealthGamePlayerController::OnTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void AStealthGamePlayerController::OnInteractPressed()
{
	FHitResult Hit;
	bool HitSuccess = GetHitResultUnderCursor(ECC_GameTraceChannel1, true, Hit);

	if (HitSuccess)
	{
		if ((Hit.Location - GetPawn()->GetActorLocation()).Length() <= 400)
		{
			AInteractable* interactable = Cast<AInteractable>(Hit.GetActor());
			if (interactable)
			{
				interactable->Interact(GetCharacter());
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursorRed, Hit.Location, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
			}

			ATelescope* Telescope = Cast<ATelescope>(Hit.GetActor());
			if (Telescope)
			{
				UE_LOG(LogTemp, Warning, TEXT("Telescope hit"));
				Telescope->OnPlayerInteraction(this);
			}


		}
	}
}

void AStealthGamePlayerController::MoveForward(float Value)
{
	CurrentlyControlledPawn->Execute_MoveForward(GetPawn(), Value);

}

void AStealthGamePlayerController::MoveRight(float Value)
{
	CurrentlyControlledPawn->Execute_MoveRight(GetPawn(), Value);

}

void AStealthGamePlayerController::AssignControlledPawn()
{
	CurrentlyControlledPawn = Cast<IUserInputInterface>(GetPawn());
	if (!CurrentlyControlledPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controller pawn assignment failed, Expect broken inputs"));
	}
}
