// Fill out your copyright notice in the Description page of Project Settings.

#include "BenevolentGodzilla.h"
#include "GodzillaPawn.h"

#include "ResourcePoint.h"
#include "BuildingSite.h"


// Sets default values
AGodzillaPawn::AGodzillaPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Character rotation only changes in Yaw, to prevent the capsule from changing orientation.
	// Ask the Controller for the full rotation if desired (ie for aiming).
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>( ACharacter::CapsuleComponentName );
	CapsuleComponent->InitCapsuleSize( 34.0f, 88.0f );
	CapsuleComponent->SetCollisionProfileName( UCollisionProfile::Pawn_ProfileName );

	CapsuleComponent->CanCharacterStepUpOn = ECB_No;
	CapsuleComponent->bShouldUpdatePhysicsVolume = true;
	CapsuleComponent->bCheckAsyncSceneOnMove = false;
	CapsuleComponent->SetCanEverAffectNavigation( false );
	CapsuleComponent->bDynamicObstacle = true;
	RootComponent = CapsuleComponent;

	MovementComponent = CreateDefaultSubobject<UGodzillaMovementComponent>( "Movement Component" );
	if ( MovementComponent )
	{
		MovementComponent->UpdatedComponent = RootComponent;
	}
	m_carrying = false;
	m_breathing_fire = false;

}

// Called when the game starts or when spawned
void AGodzillaPawn::BeginPlay()
{
	Super::BeginPlay();

	for ( TActorIterator<APlanet> ActorItr( GetWorld() ); ActorItr; ++ActorItr )
	{
		m_planet = *ActorItr;
	}

	m_StartRotation = GetActorRotation();
	
}

// Called every frame
void AGodzillaPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_TimeSinceStateChange += DeltaTime;

	switch ( m_State )
	{
	case GodzillaState::Normal:
		break;
	case GodzillaState::Happy:
	case GodzillaState::Sad:
		if ( m_TimeSinceStateChange > 3.f )
		{
			SetState( GodzillaState::Normal );
		}
		break;
	}
	if ( m_burnt_site && m_successful_burn_delay >= 0.f )
	{
		m_successful_burn_delay += DeltaTime;
		if ( m_successful_burn_delay > 2.f )
		{
			m_burnt_site->building_fired();
			if ( m_burnt_site->m_complete )
			{
				SetState( GodzillaState::Happy );
			}
			m_burnt_site = nullptr;
			m_successful_burn_delay = -1.f;
		}
	}
}

// Called to bind functionality to input
void AGodzillaPawn::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );

	// Set up gameplay key bindings
	check( PlayerInputComponent );
	PlayerInputComponent->BindAxis( "MoveForward", this, &AGodzillaPawn::MoveForward );
	PlayerInputComponent->BindAxis( "MoveRight", this, &AGodzillaPawn::MoveRight );

	PlayerInputComponent->BindAction( "Carry", IE_Pressed, this, &AGodzillaPawn::ToggleCarry );
	PlayerInputComponent->BindAction( "Fire", IE_Pressed, this, &AGodzillaPawn::StartFire );
	PlayerInputComponent->BindAction( "Fire", IE_Released, this, &AGodzillaPawn::EndFire );
}


void AGodzillaPawn::SetState( GodzillaState NewState )
{
	m_State = NewState;
	m_TimeSinceStateChange = 0.f;
}

GodzillaState AGodzillaPawn::GetState() const
{
	return m_State;
}

void AGodzillaPawn::SetCarrying( bool carry )
{
	m_carrying = carry;
}

ResourceColour AGodzillaPawn::GetCarryingColour() const
{
	return m_colour;
}

void AGodzillaPawn::SetCarryingColour(ResourceColour colour)
{
	m_colour = colour;
}

void AGodzillaPawn::ToggleCarry()
{
	if (m_carrying && m_building)
	{
		m_carrying = false;
		m_building->PlaceColour(m_colour);
	}
	else if (!m_carrying && m_resource)
	{
		m_carrying = true;
		m_colour = m_resource->GetColour();
	}
}

void AGodzillaPawn::ToggleBreathFire()
{
	if ( m_carrying )
	{
		m_breathing_fire = false;
	}
	else
	{
		m_breathing_fire = !m_breathing_fire;
	}
	if ( m_breathing_fire )
	{
		StartFire_BP();
	}
	else
	{
		EndFire_BP();
	}
}

void AGodzillaPawn::SetBreatheFire( bool fire )
{
	if ( m_carrying )
	{
		m_breathing_fire = false;
	}
	else
	{
		m_breathing_fire = fire;
	}
	if ( m_breathing_fire )
	{
		StartFire_BP();
	}
	else
	{
		EndFire_BP();
	}
}

bool AGodzillaPawn::IsBreathingFire() const
{
	return m_breathing_fire;
}

void AGodzillaPawn::StartFire()
{
	if ( m_carrying )
		return;
	m_breathing_fire = true;
	StartFire_BP();
}

void AGodzillaPawn::EndFire()
{
	m_breathing_fire = false;
	EndFire_BP();
}

void AGodzillaPawn::OverlappedResource( AResourcePoint* resource )
{
	if ( resource )
	{
		m_resource = resource;
		m_colour = resource->GetColour();
		m_carrying = true;
	}
}

void AGodzillaPawn::OverlappedBuilding( ABuildingSite* building )
{
	m_building = building;
	if ( m_carrying )
	{
		if ( !building->PlaceColour( m_colour ) )
		{
			SetState( GodzillaState::Sad );
		}
		m_carrying = false;
	}
}

void AGodzillaPawn::FireBuilding( ABuildingSite* building )
{
	m_burnt_site = building;
	m_successful_burn_delay = 0.f;
}

bool AGodzillaPawn::IsCarrying() const
{
	return m_carrying;
}

void AGodzillaPawn::MoveForward( float Value )
{
	if ( (Controller != NULL) && (Value != 0.0f) && !m_breathing_fire )
	{
		AddMovementInput( FVector( 1.f, 0.f, 0.f ), Value );
	}
}

void AGodzillaPawn::MoveRight( float Value )
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		AddMovementInput( FVector( 0.f, 1.f, 0.f ), Value );
	}
}
