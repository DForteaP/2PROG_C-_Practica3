// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Tweener.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICA3_API UTweener : public UObject
{
	GENERATED_BODY()

	AActor* Owner;	
	FVector Origin, Destiny;	
	
	FTimerHandle TimerHandle;

	float ElapsedTime;	
	float Time;

public:
	void Start(AActor* Actor, const float Time, const FVector& InTo);
	void Interp();
	
};
