// Fill out your copyright notice in the Description page of Project Settings.

#include "BenevolentGodzilla.h"
#include "ResourcePoint.h"

#include "Planet.h"


// Sets default values
AResourcePoint::AResourcePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AResourcePoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResourcePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ResourceColour AResourcePoint::GetColour() const
{
	return m_colour;
}

void AResourcePoint::OnConstruction( const FTransform& Transform )
{
	APlanet* planet = nullptr;
	for ( TActorIterator<APlanet> ActorItr( GetWorld() ); ActorItr; ++ActorItr )
	{
		planet = *ActorItr;
		if ( planet )
		{
			FVector position, normal;
			planet->GetPositionAndNormal( GetActorLocation(), position, normal, 0.f );
			SetActorLocation( position );
			break;
		}
	}
}
