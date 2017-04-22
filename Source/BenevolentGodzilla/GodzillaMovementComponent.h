// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/MovementComponent.h"
#include "GodzillaMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class BENEVOLENTGODZILLA_API UGodzillaMovementComponent : public UPawnMovementComponent
{
	GENERATED_UCLASS_BODY()
public:
	void TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction ) override;

	/** Maximum velocity magnitude allowed for the controlled Pawn. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = FloatingPawnMovement )
		float MaxSpeed;

	/** Acceleration applied by input (rate of change of velocity) */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = FloatingPawnMovement )
		float Acceleration;

	/** Deceleration applied when there is no input (rate of change of velocity) */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = FloatingPawnMovement )
		float Deceleration;

	/**
	* Setting affecting extra force applied when changing direction, making turns have less drift and become more responsive.
	* Velocity magnitude is not allowed to increase, that only happens due to normal acceleration. It may decrease with large direction changes.
	* Larger values apply extra force to reach the target direction more quickly, while a zero value disables any extra turn force.
	*/
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = FloatingPawnMovement, meta = (ClampMin = "0", UIMin = "0") )
		float TurningBoost;

private:

	FVector Forward_Vector;

	bool LimitWorldBounds();

	/** Set to true when a position correction is applied. Used to avoid recalculating velocity when this occurs. */
	UPROPERTY( Transient )
		uint32 bPositionCorrected : 1;
	
	
};
