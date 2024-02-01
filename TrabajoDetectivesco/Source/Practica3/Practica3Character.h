// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Practica3Character.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class AAInspectable;

UCLASS(config=Game)
class APractica3Character : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;



	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interact, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Zona;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Interact, meta=(AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Interact, meta=(AllowPrivateAccess = "true"))
	class UInputAction* RotateAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Interact, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* MC_Input;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Interact, meta=(AllowPrivateAccess = "true"))
	bool ModoInspeccionar = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Interact, meta = (AllowPrivateAccess = "true"))
	AAInspectable* Inspectable;
	
	
public:
	APractica3Character();

protected:
	virtual void BeginPlay();

public:
	
	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	void Inspeccionar();
	void SalirModoInspeccionar();

	void Interact();
	void Rotate(const FInputActionValue& Value);
	
	void ChangeMappingContext(const UInputMappingContext* InOldMappingContext, const UInputMappingContext* InNewMappingContext) const;
	
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};

