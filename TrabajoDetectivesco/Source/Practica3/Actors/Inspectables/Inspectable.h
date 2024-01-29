// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inspectable.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PRACTICA3_API UInspectable : public UActorComponent
{
	GENERATED_BODY()

public:
	UInspectable();

	void AttachActor(const APractica3Character* InCharacter) const;
	void Inspeccionar(const FInputActionValue& Value) const;
};
