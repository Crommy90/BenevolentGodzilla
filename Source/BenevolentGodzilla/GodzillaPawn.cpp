// Fill out your copyright notice in the Description page of Project Settings.

#include "BenevolentGodzilla.h"
#include "GodzillaPawn.h"


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
}


void AGodzillaPawn::SetCarrying( bool carry )
{
	m_carrying = carry;
}

void AGodzillaPawn::ToggleCarry()
{
	m_carrying = !m_carrying;
}

bool AGodzillaPawn::IsCarrying() const
{
	return m_carrying;
}

void AGodzillaPawn::MoveForward( float Value )
{
	if ( (Controller != NULL) && (Value != 0.0f) )
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
