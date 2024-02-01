// Copyright Epic Games, Inc. All Rights Reserved.

#include "Practica3Character.h"
#include "Practica3Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
//INPECCIONABLE
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

	//CREA SCENE COMPONENT 
	Zona = CreateDefaultSubobject<USceneComponent>(TEXT("Zona"));
	Zona->SetRelativeLocation({100.f,0.f,90.f});

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
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APractica3Character::Interact);

		//RotateItem
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &APractica3Character::Rotate);
	}
}

void APractica3Character::ChangeMappingContext(const UInputMappingContext* InOldMappingContext, const UInputMappingContext* InNewMappingContext) const
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

void APractica3Character::Interact()
{
	if(!ModoInspeccionar)
	{	
		Inspeccionar();
	}else{
		SalirModoInspeccionar();
	}
}

void APractica3Character::Rotate(const FInputActionValue& Value)
{
	const FVector LookAxisVector = Value.Get<FVector>();
	if(Inspectable->FindComponentByClass<UInspectable>())
	{
		Inspectable->FindComponentByClass<UInspectable>()->Inspeccionar(LookAxisVector);
	}
}


FHitResult HIT;

void APractica3Character::Inspeccionar()
{
	float Radio = 50.f;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(Radio);

	FCollisionQueryParams Params;
	Params.bTraceComplex = true;

	DrawDebugSphere(GetWorld(),this->GetActorLocation() + this->GetActorForwardVector() * 100.f,Radio,50,FColor::Red,false,2.f);
	GetWorld()->SweepSingleByChannel(HIT,this->GetActorLocation(),this->GetActorLocation() + this->GetActorForwardVector() * 100.f,FQuat::Identity,ECC_Visibility,CollisionShape,Params);
	
	if (HIT.IsValidBlockingHit())
	{
		if(HIT.GetActor()->FindComponentByClass<UInspectable>())
		{
			HIT.GetActor()->FindComponentByClass<UInspectable>()->CenterOnActor(this);
			if(AAInspectable* Insp = Cast<AAInspectable>(HIT.GetActor())) Inspectable = Insp;
			ChangeMappingContext(DefaultMappingContext, MC_Input);
			ModoInspeccionar = !ModoInspeccionar;
		}
	}
}

void APractica3Character::SalirModoInspeccionar()
{
	if(HIT.GetActor()->FindComponentByClass<UInspectable>())
	{
		HIT.GetActor()->FindComponentByClass<UInspectable>()->DescenterOnActor(this);
		ChangeMappingContext(MC_Input, DefaultMappingContext);
		ModoInspeccionar = !ModoInspeccionar;
	}
}

