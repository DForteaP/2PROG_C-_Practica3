// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AInspectable.generated.h"

class UTweenable;
class UInspectable;

UCLASS()
class PRACTICA3_API AAInspectable : public AActor
{
	GENERATED_BODY()

public:
	AAInspectable();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true));
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true));
	UInspectable* Inspectable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true));
	UTweenable* Tweenable;
};
