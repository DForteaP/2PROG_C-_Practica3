// Fill out your copyright notice in the Description page of Project Settings.


#include "Tweenable.h"
#include "Tweener.h"


UTweener* UTweenable::Start(const FVector& To, const float IntTime)
{
	if(!ActiveTweener)
	{
		ActiveTweener = NewObject<UTweener>(this, UTweener::StaticClass());
		if (ActiveTweener)
		{
			ActiveTweener->Start(GetOwner(), IntTime, To);
		}
	}
	return ActiveTweener;
}
