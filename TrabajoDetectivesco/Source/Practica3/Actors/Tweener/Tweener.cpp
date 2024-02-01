// Fill out your copyright notice in the Description page of Project Settings.


#include "Tweener.h"



void UTweener::Start(AActor* Actor, const float TimeTotal, const FVector& Final)
{
	Origin = Actor->GetActorLocation();
	OriginalPosition = Origin;
	Destiny = Final;
	Owner = Actor;
	Time = TimeTotal;
	
	if(Actor)
	{
		FTimerManager& TimerManager = Actor->GetWorld()->GetTimerManager();
		TimerManager.SetTimer(TimerHandle, this, &ThisClass::Interp, 1.f/60.f, true);
	}
}

void UTweener::Revert(AActor* Actor, const float TimeTotal, const FVector& Final)
{
	Origin = Actor->GetActorLocation();
	Destiny = OriginalPosition;
	Owner = Actor;
	Time = TimeTotal;
	
	if(Actor)
	{
		FTimerManager& TimerManager = Actor->GetWorld()->GetTimerManager();
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
		ElapsedTime = 0;
	}
}
