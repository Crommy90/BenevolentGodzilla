// Fill out your copyright notice in the Description page of Project Settings.

#include "BenevolentGodzilla.h"

#include "GodzillaPawn.h"

#include "GodzillaMovementComponent.h"

UGodzillaMovementComponent::UGodzillaMovementComponent( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	MaxSpeed = 1200.f;
	Acceleration = 4000.f;
	Deceleration = 8000.f;
	TurningBoost = 8.0f;
	bPositionCorrected = false;

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
			FVector change = ConsumeInputVector().GetClampedToMaxSize( 1.f );
			change *= DeltaTime;
			change *= MaxSpeed;
			//if ( !change.IsNearlyZero() )
			{
				AGodzillaPawn* Owner = Cast<AGodzillaPawn>( GetPawnOwner() );

				FVector position, normal;

				if ( Owner )
				{
					change = Owner->GetControlRotation().RotateVector( change );
					Owner->m_planet->GetPositionAndNormal( Owner->GetActorLocation() + change, position, normal );
					FRotator Actor_Rotation = Owner->GetActorRotation();
					FMatrix rotation = FRotationMatrix::MakeFromZX( normal, Owner->GetActorForwardVector() );
					FVector Delta = position - Owner->GetActorLocation();
					FHitResult OutHit;
					SafeMoveUpdatedComponent( Delta, rotation.ToQuat(), false, OutHit );
					//FRotator as_rotation = normal.Rotation();
					//as_rotation += Owner->m_StartRotation;

					Controller->SetControlRotation( rotation.Rotator() );
				}
			}

		}
		//// if it's not player controller, but we do have a controller, then it's AI
		//// (that's not following a path) and we need to limit the speed
		//else if ( IsExceedingMaxSpeed( MaxSpeed ) == true )
		//{
		//	Velocity = Velocity.GetUnsafeNormal() * MaxSpeed;
		//}

		//LimitWorldBounds();
		//bPositionCorrected = false;

		//// Move actor
		//FVector Delta = Velocity * DeltaTime;

		//if ( !Delta.IsNearlyZero( 1e-6f ) )
		//{
		//	const FVector OldLocation = UpdatedComponent->GetComponentLocation();
		//	FQuat Rotation = UpdatedComponent->GetComponentQuat();

		//	AGodzillaPawn* Owner = Cast<AGodzillaPawn>(GetPawnOwner());

		//	FVector position, normal;

		//	if ( Owner )
		//	{
		//		Owner->m_planet->GetPositionAndNormal( Delta + Owner->GetActorLocation(), position, normal );
		//		Delta = position - Owner->GetActorLocation();
		//	}

		//	FHitResult Hit( 1.f );
		//	SafeMoveUpdatedComponent( Delta, Rotation, true, Hit );

			//if ( Hit.IsValidBlockingHit() )
			//{
			//	HandleImpact( Hit, DeltaTime, Delta );
			//	// Try to slide the remaining distance along the surface.
			//	SlideAlongSurface( Delta, 1.f - Hit.Time, Hit.Normal, Hit, true );
			//}
			//Owner->SetActorLocation( position );
			//Owner->SetActorRotation( normal.Rotation().Quaternion());

			//// Update velocity
			//// We don't want position changes to vastly reverse our direction (which can happen due to penetration fixups etc)
			//if ( !bPositionCorrected )
			//{
			//	const FVector NewLocation = UpdatedComponent->GetComponentLocation();
			//	Velocity = ((NewLocation - OldLocation) / DeltaTime);
			//}
		//}

		// Finalize
		UpdateComponentVelocity();
	}
}


bool UGodzillaMovementComponent::LimitWorldBounds()
{
	AWorldSettings* WorldSettings = PawnOwner ? PawnOwner->GetWorldSettings() : NULL;
	if ( !WorldSettings || !WorldSettings->bEnableWorldBoundsChecks || !UpdatedComponent )
	{
		return false;
	}

	const FVector CurrentLocation = UpdatedComponent->GetComponentLocation();
	if ( CurrentLocation.Z < WorldSettings->KillZ )
	{
		Velocity.Z = FMath::Min( GetMaxSpeed(), WorldSettings->KillZ - CurrentLocation.Z + 2.0f );
		return true;
	}

	return false;
}