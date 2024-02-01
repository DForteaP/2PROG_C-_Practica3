// Fill out your copyright notice in the Description page of Project Settings.


#include "Tweenable.h"
#include "Tweener.h"



UTweener* UTweenable::Start(const FVector& Destiny, const float TimeTotal)
{
		ActiveTweener = NewObject<UTweener>(this, UTweener::StaticClass());
		if (ActiveTweener)
		{
			ActiveTweener->Start(GetOwner(), TimeTotal, Destiny);
		}
	return ActiveTweener;
}


UTweener* UTweenable::Revert(const FVector& Destiny, const float TimeTotal)
{
	if (ActiveTweener)
	{
		ActiveTweener->Revert(GetOwner(), TimeTotal, Destiny);
	}
	return ActiveTweener;
}