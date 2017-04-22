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
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>( ACharacter::CapsuleComponentName );
	CapsuleComponent->InitCapsuleSize( 34.0f, 88.0f );
	CapsuleComponent->SetCollisionProfileName( UCollisionProfile::Pawn_ProfileName );

	CapsuleComponent->CanCharacterStepUpOn = ECB_No;
	CapsuleComponent->bShouldUpdatePhysicsVolume = true;
	CapsuleComponent->bCheckAsyncSceneOnMove = false;
	CapsuleComponent->SetCanEverAffectNavigation( false );
	CapsuleComponent->bDynamicObstacle = true;
	RootComponent = CapsuleComponent;

	//MovementComponent = CreateDefaultSubobject<UGodzillaMovementComponent>( "Movement Component" );
	//if ( MovementComponent )
	//{
	//	MovementComponent->UpdatedComponent = RootComponent;
	//}

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
}


void AGodzillaPawn::SetCarrying( bool carry )
{
	m_carrying = carry;
}

bool AGodzillaPawn::IsCarrying() const
{
	return m_carrying;
}

void AGodzillaPawn::MoveForward( float Value )
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation( 0, Rotation.Yaw, 0 );

		// get forward vector
		const FVector Direction = FRotationMatrix( YawRotation ).GetUnitAxis( EAxis::X );
		AddMovementInput( Direction, Value );
	}
}

void AGodzillaPawn::MoveRight( float Value )
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation( 0, Rotation.Yaw, 0 );

		// get right vector 
		const FVector Direction = FRotationMatrix( YawRotation ).GetUnitAxis( EAxis::Y );
		// add movement in that direction
		AddMovementInput( Direction, Value );
	}
}
