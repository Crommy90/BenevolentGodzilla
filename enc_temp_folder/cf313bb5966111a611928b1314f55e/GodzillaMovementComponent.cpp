// Fill out your copyright notice in the Description page of Project Settings.

#include "BenevolentGodzilla.h"

#include "GodzillaPawn.h"

#include "GodzillaMovementComponent.h"

UGodzillaMovementComponent::UGodzillaMovementComponent( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	MaxSpeed = 1200.f;
	AccelerationRate = 4000.f;
	Deceleration = 8000.f;
	TurningBoost = 8.0f;

	ResetMoveState();
}

void UGodzillaMovementComponent::TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction )
{
	if ( ShouldSkipUpdate( DeltaTime ) )
	{
		return;
	}

	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if ( !PawnOwner || !UpdatedComponent )
	{
		return;
	}

	AController* Controller = PawnOwner->GetController();
	if ( Controller && Controller->IsLocalController() )
	{
		// apply input for local players but also for AI that's not following a navigation path at the moment
		if ( Controller->IsLocalPlayerController() == true || Controller->IsFollowingAPath() == false )
		{
			const FVector OldVelocity = LocalVelocity;
			FVector Additional_Velocity = ConsumeInputVector().GetClampedToMaxSize( 1.f );
			FRotator delta_rot = FRotator::ZeroRotator;
			if ( Additional_Velocity.IsNearlyZero() )
			{
				const float VelSize = FMath::Max( LocalVelocity.Size() - FMath::Abs( Deceleration ) * DeltaTime, 0.f );
				LocalVelocity = LocalVelocity.GetSafeNormal() * VelSize;
			}
			else
			{
				if ( Additional_Velocity.Y != 0.f )
				{
					delta_rot.Yaw = Additional_Velocity.Y * DeltaTime * 45.f;
				}
				Additional_Velocity.Y = 0.f;
				Additional_Velocity *= AccelerationRate;
				Additional_Velocity *= DeltaTime;
				LocalVelocity += Additional_Velocity;
			}
			// Apply acceleration and clamp velocity magnitude.
			const float NewMaxSpeed = (IsExceedingMaxSpeed( MaxSpeed )) ? LocalVelocity.Size() : MaxSpeed;
			LocalVelocity = LocalVelocity.GetClampedToMaxSize( NewMaxSpeed );


			//if ( !LocalVelocity.IsNearlyZero() )
			{
				AGodzillaPawn* Owner = Cast<AGodzillaPawn>( GetPawnOwner() );

				FVector position, normal;

				if ( Owner )
				{
					Velocity = Owner->GetActorRotation().RotateVector( LocalVelocity );
					Owner->m_planet->GetPositionAndNormal( Owner->GetActorLocation() + (Velocity * DeltaTime ), position, normal );
					FRotator Actor_Rotation = Owner->GetActorRotation();
					FMatrix rotation = FRotationMatrix::MakeFromZX( normal, Owner->GetActorForwardVector() );
					FRotator roation_again = rotation.Rotator() + delta_rot;
					FHitResult OutHit;
					SafeMoveUpdatedComponent( position - GetActorLocation(), roation_again.Quaternion(), false, OutHit );
					Controller->SetControlRotation( roation_again );
				}
			}

		}

		// Finalize
		UpdateComponentVelocity();
	}
}
