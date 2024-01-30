// Copyright Epic Games, Inc. All Rights Reserved.

#include "Practica3Character.h"
#include "Practica3Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Actors/Inspectables/AInspectable.h"
#include "Actors/Inspectables/Inspectable.h"


//////////////////////////////////////////////////////////////////////////
// APractica3Character

APractica3Character::APractica3Character()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));


	Zona = CreateDefaultSubobject<USceneComponent>(TEXT("Zona"));
	Zona->SetRelativeLocation({90.f,0.f,60.f});

}

void APractica3Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

//////////////////////////////////////////////////////////////////////////// Input

void APractica3Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APractica3Character::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APractica3Character::Look);

		//Interact
		EnhancedInputComponent->BindAction(Inspeccionar, ETriggerEvent::Started, this, &APractica3Character::InspectActor);

		//Inspect
		EnhancedInputComponent->BindAction(GirarObjeto, ETriggerEvent::Triggered, this, &APractica3Character::LookItem);
	}
}


void APractica3Character::AddMappingContext(const UInputMappingContext* InOldMappingContext, const UInputMappingContext* InNewMappingContext) const
{
	//Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(InOldMappingContext);
			Subsystem->AddMappingContext(InNewMappingContext, 0);
		}
	}
}

void APractica3Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APractica3Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APractica3Character::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool APractica3Character::GetHasRifle()
{
	return bHasRifle;
}


void APractica3Character::ThrowInspectMode()
{
	FHitResult OutHit;

	float RadiusSphere = 50.f;
		
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(RadiusSphere);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
					
	GetWorld()->SweepSingleByChannel(
		OutHit,
		this->GetActorLocation(),
		this->GetActorLocation() + this->GetActorForwardVector() * 100.f,
		FQuat::Identity,
		ECC_Visibility,
		CollisionShape,
		QueryParams
	);
		
#if WITH_EDITOR
	DrawDebugSphere(GetWorld(),
					this->GetActorLocation(),
					RadiusSphere,
					100,
					FColor::Blue,
					false,
					5.f
	);
#endif

	if (OutHit.IsValidBlockingHit())
	{
		if(UInspectable* InspectableActor = OutHit.GetActor()->FindComponentByClass<UInspectable>())
		{
			InspectableActor->AttachActor(this);
			IsInspecting = true;
			
			if(UInspectable* Insp = Cast<UInspectable>(OutHit.GetActor())) InspectableActor = Insp;
			
			AddMappingContext(DefaultMappingContext, InspectMC);
		}
	}
}

void APractica3Character::RemoveInspectMode()
{
	AddMappingContext(InspectMC, DefaultMappingContext);
	IsInspecting = false;
}

void APractica3Character::InspectActor()
{
	if(!IsInspecting)
	{	
		ThrowInspectMode();
	}else
	{
		RemoveInspectMode();
	}
}

void APractica3Character::LookItem(const FInputActionValue& Value)
{
	const FVector LookAxisVector = Value.Get<FVector>();

	if(UInspectable* InspectableComponent = Inspectable->FindComponentByClass<UInspectable>())
	{
		InspectableComponent->Inspeccionar(LookAxisVector);
	}
}
