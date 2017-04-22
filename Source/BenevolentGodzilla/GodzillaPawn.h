// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"

#include "GodzillaMovementComponent.h"
#include "Planet.h"

#include "GodzillaPawn.generated.h"

UCLASS()
class BENEVOLENTGODZILLA_API AGodzillaPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGodzillaPawn();

	/** The CapsuleComponent being used for movement collision (by CharacterMovement). Always treated as being vertically aligned in simple collision check functions. */
	UPROPERTY( Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") )
		class UCapsuleComponent* CapsuleComponent;

	///** Movement component used for movement logic in various movement modes (walking, falling, etc), containing relevant settings and functions to control movement. */
	UPROPERTY( Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") )
		class UGodzillaMovementComponent* MovementComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward( float Value );

	/** Called for side to side input */
	void MoveRight( float Value );

	bool m_carrying;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION( BlueprintCallable, Category = "Godzilla" )
		bool IsCarrying() const;

	UFUNCTION( BlueprintCallable, Category = "Godzilla" )
		void SetCarrying( bool carry );

	UFUNCTION( BlueprintCallable, Category = "Godzilla" )
		void ToggleCarry();

	UPROPERTY( EditAnywhere )
		APlanet* m_planet;

	FRotator m_StartRotation;

	
	
};
