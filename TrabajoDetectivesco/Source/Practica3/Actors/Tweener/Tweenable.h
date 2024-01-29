// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Tweenable.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PRACTICA3_API UTweenable : public UActorComponent
{
	GENERATED_BODY()

public:
	UTweenable();

	TObjectPtr<UTweener> ActiveTweener;

	float Time = 1.f;

	UFUNCTION(BlueprintCallable)
	UTweener* Start(const FVector& Destiny, float Time);

	float GetTime() const {return Time;};
	
};
