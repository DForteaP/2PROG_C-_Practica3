// Fill out your copyright notice in the Description page of Project Settings.


#include "AInspectable.h"

#include "Inspectable.h"
#include "Practica3/Actors/Tweener/Tweenable.h"


// Sets default values
AAInspectable::AAInspectable()
{
	
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);	

	
#if WITH_EDITOR
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshFinder(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone"));
	
	if(StaticMeshFinder.Succeeded()) MeshComponent->SetStaticMesh(StaticMeshFinder.Object);
	
#endif

	Inspectable = CreateDefaultSubobject<UInspectable>(TEXT("Inspectable"));

	Tweenable = CreateDefaultSubobject<UTweenable>(TEXT("Tweenable"));
	
}



