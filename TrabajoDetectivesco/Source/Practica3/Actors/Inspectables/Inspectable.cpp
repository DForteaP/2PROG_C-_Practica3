// Fill out your copyright notice in the Description page of Project Settings.


#include "Inspectable.h"

#include "Practica3/Practica3Character.h"
#include "Practica3/Actors/Inspectables/AInspectable.h"
#include "Practica3/Actors/Tweener/Tweenable.h"


// Sets default values for this component's properties
UInspectable::UInspectable()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UInspectable::AttachActor(const APractica3Character* InCharacter) const
{
	AAInspectable* Inspectable = Cast<AAInspectable>(GetOwner());
	if(!Inspectable) return;

	UTweenable* Tweenable = Inspectable->FindComponentByClass<UTweenable>();
	if(!Tweenable) return;
	
	if(const USceneComponent* PointToInspect = InCharacter->FindComponentByClass<USceneComponent>()){
		Tweenable->Start(PointToInspect->GetComponentLocation(), Tweenable->GetTime());
	}	
}

void UInspectable::Inspeccionar(const FInputActionValue& Value) const
{
	const FVector RotateAxis = Value.Get<FVector>();
	
	if(AAInspectable* InspectableActor = Cast<AAInspectable>(GetOwner()))
	{
		InspectableActor->AddActorLocalRotation(
			FQuat(FRotator(RotateAxis.Y,RotateAxis.Z,RotateAxis.X)),
			false,
			nullptr,
			ETeleportType::None);
	}
}