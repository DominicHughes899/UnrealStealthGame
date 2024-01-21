// Copyright Epic Games, Inc. All Rights Reserved.

#include "StealthGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AStealthGameCharacter::AStealthGameCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a held item boom...
	HeldItemBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Held Item Boom"));
	HeldItemBoom->SetupAttachment(GetMesh());
	HeldItemBoom->TargetArmLength = 100.f;
	HeldItemBoom->bEnableCameraLag = true;
	HeldItemBoom->bEnableCameraRotationLag = true;
	HeldItemBoom->CameraLagSpeed = 4.f;
	HeldItemBoom->CameraRotationLagSpeed = 1.f;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AStealthGameCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

bool AStealthGameCharacter::AttachHeldItem(AActor* ItemToAttach, FName Tag)
{
	// Returns true if attachment is successful

	bool Success = false;

	if (!HeldItem)
	{
		Success = true;

		ItemToAttach->AttachToComponent(HeldItemBoom, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		Tags.Add(Tag);

		HeldItem = ItemToAttach;
	}

	return Success;

}

void AStealthGameCharacter::ClearHeldItem()
{
	if (HeldItem)
	{
		Tags.Empty();

		HeldItem->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		HeldItem->Destroy();
		HeldItem = nullptr;
	}
}

