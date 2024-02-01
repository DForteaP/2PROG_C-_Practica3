// Fill out your copyright notice in the Description page of Project Settings.


#include "Inspectable.h"

#include "Practica3/Practica3Character.h"
#include "Practica3/Actors/Inspectables/AInspectable.h"
#include "Practica3/Actors/Tweener/Tweenable.h"


AAInspectable* Inspectable;
UTweenable* Tweenable;



UInspectable::UInspectable()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInspectable::CenterOnActor(const APractica3Character* Character) const
{
	Inspectable = Cast<AAInspectable>(GetOwner());
	if(!Inspectable) return;

	Tweenable = Inspectable->FindComponentByClass<UTweenable>();
	if(!Tweenable) return;
	
	if(const USceneComponent* PointToInspect = Character->FindComponentByClass<USceneComponent>()){
		Tweenable->Start(PointToInspect->GetComponentLocation() + Character->GetActorForwardVector() * 100, Tweenable->GetTime());
	}	
}

void UInspectable::DescenterOnActor(const APractica3Character* Character) const
{
	if(const USceneComponent* PointToInspect = Character->FindComponentByClass<USceneComponent>()){
		Tweenable->Revert(PointToInspect->GetComponentLocation() + Character->GetActorForwardVector() * 100, Tweenable->GetTime());
	}
}

void UInspectable::Inspeccionar(const FInputActionValue& Value) const
{
	const FVector RotateAxis = Value.Get<FVector>();
	if(AAInspectable* InspectableActor = Cast<AAInspectable>(GetOwner()))
	{
		InspectableActor->AddActorLocalRotation(FQuat(FRotator(RotateAxis.Y,RotateAxis.Z,RotateAxis.X)),false,nullptr,ETeleportType::None);
	}
}