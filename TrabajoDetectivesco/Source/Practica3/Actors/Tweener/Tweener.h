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
	FVector Origin;
	FVector Destiny;
	FVector OriginalPosition;
	
	FTimerHandle TimerHandle;

	float ElapsedTime;	
	float Time;

public:
	void Start(AActor* Actor, const float Time, const FVector& Destiny);
	void Revert(AActor* Actor, const float Time, const FVector& OriginalPosition);
	void Interp();
	
};
