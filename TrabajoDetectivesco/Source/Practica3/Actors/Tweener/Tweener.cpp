// Fill out your copyright notice in the Description page of Project Settings.


#include "Tweener.h"


void UTweener::Start(AActor* InTweenActor, const float InInterpTime, const FVector& InTo)
{
	Origin = InTweenActor->GetActorLocation();
	Destiny = InTo;
	Owner = InTweenActor;
	Time = InInterpTime;
	
	if(InTweenActor)
	{
		FTimerManager& TimerManager = InTweenActor->GetWorld()->GetTimerManager();
		TimerManager.SetTimer(TimerHandle, this, &ThisClass::Interp, 1.f/60.f, true);
	}
}

void UTweener::Interp()
{
	FTimerManager& TimerManager = Owner->GetWorld()->GetTimerManager();
	ElapsedTime += TimerManager.GetTimerRate(TimerHandle);
	
	const FVector InterpPosition = FMath::Lerp(Origin, Destiny, ElapsedTime/Time);
	Owner->SetActorLocation(InterpPosition);
	

	if (FMath::IsNearlyEqual(Time, ElapsedTime, 0.01f))
	{
		TimerManager.ClearTimer(TimerHandle);
	}
}